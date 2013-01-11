#include <stdio.h>
#include "commands.h"

extern const char *help_text;

int cmd_help(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("%s\n", help_text);
    }
    else {
        // TODO: print help for specific command
    }
    return 0;
}
