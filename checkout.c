#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "checkout.h"
#include "commit.h"
#include "object.h"
#include "path.h"
#include "tree.h"

int cmd_checkout(int argc, const char *argv[]) {
    new_index((char *)(argv[1]));
    copy_out();
    return 0;
}

void new_index(char *hash) {
    char *indexpath = get_repo_troll_dir();
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");
    printf("New index at %s\n",indexpath);

    int index = open(indexpath, O_WRONLY | O_TRUNC, 0644);
    free(indexpath);
    lseek(index, 0, SEEK_SET);
    int sout = dup(STDOUT_FILENO);
    dup2(index,STDOUT_FILENO);

    print_object(hash);
    dup2(sout,STDOUT_FILENO);
}

void copy_out() {
    char *indexpath = get_repo_troll_dir();
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");

    FILE *findex = fopen(indexpath, "r");
    free(indexpath);
    fseek(findex, 0, SEEK_SET);
    
    char hash[41];
    
    int newfile;
    char *trollpath = get_repo_troll_dir();
    char *repo_path = (char *) malloc(strlen(trollpath) - 7);
    strncat(repo_path,trollpath,strlen(trollpath) - 7);

    free(trollpath);
    char *newpath;
    char name[256];
    int sout;
    char *lastchar;
    sout = dup(STDOUT_FILENO);
    while(fgets(hash, 41, findex)) {
      fseek(findex,1,SEEK_CUR);
      fgets(name, 256, findex);

      newpath = (char *) malloc(strlen(repo_path) + strlen(name));
      strcat(newpath, repo_path);
      strcat(newpath, name);
      lastchar = strstr(newpath,"\n");
      *lastchar = '\0';

      newfile = open(newpath, O_WRONLY | O_TRUNC, 0644);
      printf("%s\n",newpath);
      dup2(newfile,STDOUT_FILENO);
      print_object(hash);
      dup2(sout,STDOUT_FILENO);
      close(newfile);
    }
}
