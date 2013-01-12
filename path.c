#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "path.h"

/* Returns full path of generated .troll directory */
char *init_troll_dir(const char *base) {
    char *dir = getcwd(NULL, 0);
    if (base) {
        dir = (char *) realloc(dir, strlen(dir) + strlen(base) + 8);
    }
    else {
        dir = (char *) realloc(dir, strlen(dir) + 8);
    }
    strcat(dir, "/");
    if (base) {
        strncat(dir, base, strlen(dir));
        strcat(dir, "/");
        mkdir(base, 0755);
    }
    strcat(dir, TROLL_DIR);
    mkdir(dir, 0755);
    return dir;
}
