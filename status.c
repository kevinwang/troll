#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <openssl/sha.h>
#include "commands.h"
#include "path.h"
#include "index.h"

int cmd_status(int argc, const char *argv[]) {
    die_if_not_troll_repo();
    char *currdir = getcwd();
    char *trollpath = get_repo_troll_dir();
    char *usta = (char *)malloc(strlen(trollpath) + 12);
    strcat(usta, trollpath);
    strcat(usta, "unstaged.tmp");
    char *utra = (char *)malloc(strlen(trollpath) + 13);
    strcat(utra, trollpath);
    strcat(utra, "untracked.tmp");
    int unstaged = open(usta,O_RDWR | O_CREAT, 0644);
    int untracked = open(utra,O_RDWR | O_CREAT, 0644);

    char *repo_path = (char *) malloc(strlen(trollpath) - 7);
    strncat(repo_path,trollpath,strlen(trollpath) - 7);

    free(usta);
    free(utra);
    search_dirs(unstaged, untracked, repo_path);
    //print both files here
    printf("Changes not staged for commit: \n");
    printf("Untracked files: \n");

    chdir(currdir);
    close(unstaged);
    close(untracked);
    //    unlink("unstaged.tmp");
    //unlink("untracked.tmp");    
    return 0;
}

char *file_hash(char *filename) {
    int fd;
    fd = open(filename, O_RDONLY);
    struct stat buf;
    fstat(fd, &buf);
    char *data = (char *) malloc((size_t) buf.st_size + 15);
    sprintf(data, "blob %lu", (unsigned long) buf.st_size);
    int left_part_len = strlen(data) + 1;
    read(fd, data + left_part_len, buf.st_size);
    int full_len = left_part_len + buf.st_size;
    char *hash = hash_object(data, full_len);
    close(fd);
    return hash;
}

void search_dirs(int unstaged, int untracked, char *curr) {
    DIR *dir = opendir(curr);
    struct dirent *dirstuff;
    while(dirstuff = readdir(dir)) {
      printf("%s\n",dirstuff->d_name);
      if(dirstuff->d_type == DT_DIR && *(dirstuff->d_name) != '.') {
	char *currnew = (char *)malloc(strlen(curr) + strlen(dirstuff->d_name)+1);
	strcat(currnew, dirstuff->d_name);
	strcat(currnew, "/");
	printf("currnew: %s\n",currnew);
	search_dirs(unstaged,untracked,currnew);
      }
      else {
	int ind = index_file_check(file_hash(dirstuff->d_name),dirstuff->d_name);
	printf("name: %s\n",dirstuff->d_name);
	if(ind < 0) {
	  write(unstaged,dirstuff->d_name, strlen(dirstuff->d_name));
	  write(unstaged,"\n",1);
	}
	else if(ind > 0) {
	  write(untracked,dirstuff->d_name,strlen(dirstuff->d_name));
	  write(untracked,"\n",1);
	}
      }
    }   
}
