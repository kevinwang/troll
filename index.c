#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "index.h"
#include "path.h"

void add_to_index(char *hash, char *path) {
    int filecheck = index_file_check(hash,path);
    if(!filecheck)
      return;

    int stuff = 0;
    char *indexpath = get_repo_troll_dir();
    int repo_path_len = strlen(indexpath) - 7;
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");

    if(filecheck > 0) {
      FILE *findex = fopen(indexpath, "r+");
      free(indexpath);
      stuff = fseek(findex, 0, SEEK_SET);
      
      char str[256];
      int line = 1;
      while(fgets(str, 256, findex)) {
	if(line == filecheck) {
	  stuff = fseek(findex, -strlen(str), SEEK_CUR);
	  stuff = fwrite(hash, 40, 1, findex);
	  stuff = fseek(findex, 1, SEEK_CUR);
	  stuff = fwrite(path, strlen(path), 1, findex);
	  stuff = fclose(findex);
	  return;
	}
	line++;
      }
      fclose(findex);
    }

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
 * Returns 0 if exact file is found,
 * The line of the file in index if found with different hash,
 * or -1 if file is not found in .troll/index
 */
int index_file_check(char *hash, char *path) {
    char *indexpath = get_repo_troll_dir();
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");

    FILE *findex = fopen(indexpath, "r");
    free(indexpath);
    fseek(findex, 0, SEEK_SET);
    
    char str[256];
    int line = 1;
    while(fgets(str, 256, findex)) {
      if(strstr(str,hash)) {
	return 0;
      }
      if(strstr(str,path)) {
	return line;
      }
      line++;
    }
    fclose(findex);
    return -1;
}
