#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "commands.h"
#include "object.h"

int cmd_add(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("Nothing specified, nothing added.\n");
        return 0;
    }
    struct stat buf;
    if (stat(argv[1], &buf) != 0) {
        printf("Ain't gon' work: %s\n", strerror(errno));
        return 128;
    }
    write_blob((char *) argv[1]);
    return 0;
}
