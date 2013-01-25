#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "path.h"

int cmd_ls_files(int argc, const char *argv[]) {
    die_if_not_troll_repo();
    char *indexpath = get_repo_troll_dir();
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");
    FILE *index = fopen(indexpath, "r");
    free(indexpath);

    char line[256];
    while (fgets(line, 256, index) != NULL) {
        printf("%s", line + 41);
    }

    fclose(index);
    return 0;
}
