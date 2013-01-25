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
    return 0;
}

void new_index(char *hash) {
    char *indexpath = get_repo_troll_dir();
    indexpath = (char *) realloc(indexpath, strlen(indexpath) + 5);
    strcat(indexpath, "index");

    int index = open(indexpath, O_WRONLY | O_TRUNC, 0644);
    free(indexpath);
    lseek(index, 0, SEEK_SET);
    int sout = dup(STDOUT_FILENO);
    dup2(index,STDOUT_FILENO);

    print_object(hash);
    dup2(sout,STDOUT_FILENO);
}
