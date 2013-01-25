#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "commit.h"
#include "path.h"

int cmd_commit(int argc, const char *argv[]) {
    die_if_not_troll_repo();
    if (argc < 3 || strcmp(argv[1], "-m") != 0) {
        printf("Please run 'troll commit -m \"your commit message here\".\n");
        return 0;
    }
    commit(argv[2]);
    return 0;
}
