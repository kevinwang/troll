#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "commands.h"
#include "path.h"

int cmd_init(int argc, const char *argv[]) {
    char *dir = init_troll_dir(argc > 1 ? argv[1] : NULL);
    printf("Initialized empty troll repository in %s\n", dir);
    free(dir);
    return 0;
}
