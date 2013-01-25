#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"
#include "commit.h"
#include "object.h"
#include "path.h"

void print_log(char *hash) {
    if (!hash) {
        return;
    }
    print_object(hash);
    printf("\n");
    print_log(get_parent(hash));
}

int cmd_log(int argc, const char *argv[]) {
    die_if_not_troll_repo();
    char *path = get_repo_troll_dir();
    path = (char *) realloc(path, strlen(path) + 5);
    strcat(path, "HEAD");
    int fd = open(path, O_RDONLY);

    char *hash = (char *) malloc(41 * sizeof(char));
    read(fd, hash, 40);
    printf("%s\n", hash);

    if (strcmp(hash, "master") == 0) {
        char *path2 = get_repo_troll_dir();
        path2 = (char *) realloc(path2, strlen(path2) + 7);
        strcat(path2, "master");
        int fd = open(path2, O_RDONLY);

        read(fd, hash, 40);
    }

    print_log(hash);

    free(hash);
    close(fd);
    return 0;
}
