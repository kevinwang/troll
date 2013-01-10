#include <stdio.h>
#include "commands.h"

int cmd_help(int argc, const char *argv[]) {
    printf("Commonly used commands are:\nhelp\t\tPrint out help.\n");
    return 0;
}
