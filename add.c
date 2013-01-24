#include <errno.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "commands.h"
#include "object.h"

int ftw_add(const char *fpath, const struct stat *sb, int typeflag) {
    char *cwd = getcwd(NULL, 0);
    if (typeflag == FTW_F) {
        write_blob((char *) fpath);
    }
    chdir(cwd);
    free(cwd);
    return 0;
}

int cmd_add(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("Nothing specified, nothing added.\n");
        return 0;
    }
    char *cwd = getcwd(NULL, 0);
    int i;
    for (i = 1; i < argc; i++) {
        printf("Adding: %s\tLength: %lu\tcwd: %s\n", argv[i], strlen(argv[i]), getcwd(NULL, 0));
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
        chdir(cwd);
    }
    free(cwd);
    return 0;
}
