#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "index.h"
#include "path.h"

void add_to_index(char *hash, char *path) {
    int stuff;

    char *indexpath = get_repo_troll_dir();
    int repo_path_len = strlen(indexpath) - 7;
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");

    int indexfd = open(indexpath, O_RDWR);
    free(indexpath);
    lseek(indexfd, 0, SEEK_END);

    char *fullpath = realpath(path, NULL);
    char *relpath = fullpath + repo_path_len;

    stuff = write(indexfd, hash, 40);
    stuff = write(indexfd, " ", 1);
    stuff = write(indexfd, relpath, strlen(relpath));
    stuff = write(indexfd, "\n", 1);
    close(indexfd);
    free(fullpath);
}

/*
 * Returns 0 if exact file is found
 * 1 if file is found with different hash
 * -1 if file is not found in .troll
 */
int index_file_check(char *hash, char *path) {
    char *indexpath = get_repo_troll_dir();
    int repo_path_len = strlen(indexpath) - 7;
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");

    char *fullpath = realpath(path, NULL);
    char *relpath = fullpath + repo_path_len;
    
    FILE *findex = fopen(indexpath, "r");
    free(indexpath);
    fseek(findex, 0, SEEK_SET);
    
    char str[256];
    while(fgets(str, 256, findex)) {
      if(strstr(str,hash)) {
	return 0;
      }
      if(strstr(str,path)) {
	return 1;
      }
    }
    fclose(findex);
    return -1;
}
