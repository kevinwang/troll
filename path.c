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
    free(dir);

    return trolldir;
}

char *get_repo_troll_dir() {
  char *cwd = getcwd(NULL, 0);
  int ret;
  ret = chdir(".troll");
  if (ret == 0 ) {
    cwd = (char *) realloc(strlen(cwd) + 9);
    strcat(cwd, "/.troll/");
    return cwd;
  }
  if (!strcmp(cwd, "/")) {
    return NULL;
  }
  ret = chdir("..");
  return get_repo_troll_dir();
}
