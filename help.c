#include <stdio.h>
#include <string.h>
#include "commands.h"

extern const char *help_text;
const char *h_help = "\n\ttroll-help - display help information about troll\n\n"
                     "\ttroll help <command>\n\n"
                     "\tWith no command, a list of all available commands are printed on the standard output\n\n"
                     "\tIf a command is named, then a short \"man\" is printed to the standard output\n";
const char *h_init = "\n\ttroll-init - initialize an empty troll repository\n\n"
                     "\ttroll init <directory>\n\n"
                     "\tThis command creates an empty troll repository, a .troll directory with subdirectories for objects.\n\n"
                     "\tIf no <directory> argument is given, the current directory becomes a troll repo.\n\n"
                     "\tOtherwise, a new directory is made containing a troll repo.\n";
const char *h_face = "\n\ttroll-face - ?\n";

int cmd_help(int argc, const char *argv[]) {
    if (argc == 1) {
        printf("%s\n", help_text);
    }
    else {
        // TODO: print help for specific command
      if(!strcmp(argv[1],"help")) {
	printf("%s\n", h_help);
      }
      else if(!strcmp(argv[1],"init")) {
	printf("%s\n", h_init);
      }
      else if(!strcmp(argv[1],"face")) {
	printf("%s\n", h_face);
      }
      else {
	printf("No manual entry for troll%s\n", argv[1]);
      }
    }
    return 0;
}
