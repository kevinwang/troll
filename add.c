#include <errno.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "commands.h"
#include "object.h"
#include "path.h"

int ftw_add(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_F) {
        write_blob((char *) fpath);
    }
    return 0;
}

int cmd_add(int argc, const char *argv[]) {
    die_if_not_troll_repo();
    if (argc == 1) {
        printf("Nothing specified, nothing added.\n");
        return 0;
    }
    int i;
    for (i = 1; i < argc; i++) {
        struct stat buf;
        if (stat(argv[i], &buf) != 0) {
            printf("Ain't gon' work: %s\n", strerror(errno));
            return 128;
        }
        if (S_ISDIR(buf.st_mode)) {
            ftw(argv[i], ftw_add, 256);
        }
        else {
            write_blob((char *) argv[i]);
        }
    }
    return 0;
}
