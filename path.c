#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <glob.h>
#include "path.h"

/* Returns full path of generated .troll directory */
char *init_troll_dir(const char *base) {
    char *dir = getcwd(NULL, 0);
    if (base) {
        dir = (char *) realloc(dir, strlen(dir) + strlen(base) + 9);
    }
    else {
        dir = (char *) realloc(dir, strlen(dir) + 9);
    }
    strcat(dir, "/");
    if (base) {
        strncat(dir, base, strlen(dir));
        strcat(dir, "/");
        mkdir(base, 0755);
    }
    strcat(dir, TROLL_DIR);
    strcat(dir, "/");
    mkdir(dir, 0755);

    char *trolldir = (char *) malloc(strlen(dir) + 1);
    memcpy(trolldir, dir, strlen(dir) + 1);

    dir = (char *) realloc(dir, strlen(dir) + 7);
    strcat(dir, "objects");
    mkdir(dir, 0755);

    char *indexpath = (char *) malloc(strlen(dir) + 6);
    memcpy(indexpath, trolldir, strlen(trolldir) + 1);
    strcat(indexpath, "index");
    int fd = open(indexpath, O_CREAT, 0644);
    close(fd);

    char *headpath = (char *) malloc(strlen(dir) + 5);
    memcpy(headpath, trolldir, strlen(trolldir) + 1);
    strcat(headpath, "HEAD");
    int headfd = open(headpath, O_CREAT, 0644);
    close(headfd);

    free(dir);

    return trolldir;
}

char *recursive_get_repo_troll_dir() {
  char *cwd = getcwd(NULL, 0);
  int ret;
  ret = chdir(".troll");
  if (ret == 0 ) {
    cwd = (char *) realloc(cwd, strlen(cwd) + 9);
    strcat(cwd, "/.troll/");
    return cwd;
  }
  if (!strcmp(cwd, "/")) {
    return NULL;
  }
  ret = chdir("..");
  return recursive_get_repo_troll_dir();
}

char *get_repo_troll_dir() {
    char *cwd = getcwd(NULL, 0);
    char *trolldir = recursive_get_repo_troll_dir();
    chdir(cwd);
    free(cwd);
    return trolldir;
}

void die_if_not_troll_repo() {
    char *trolldir = get_repo_troll_dir();
    if (trolldir) {
        free(trolldir);
    }
    else {
        free(trolldir);
        printf("Not a troll repository.\n");
        exit(128);
    }
}
