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
const char *h_add = "\n\ttroll-add - add file(s) to the working directory\n\n"
                    "\ttroll add <file>...\n\n"
  "\tThe specified files are added to the index to be committed to a tree.\n\n";
const char *h_ls_files = "\n\ttroll-ls-files\n\n"
                         "\ttroll ls-files\n\n"
                         "\tls-files lists the files being tracked in the .troll directory\n\n";
const char *h_commit = "\n\ttroll-commit\n\n"
                       "\ttroll commit -m <message>\n\n"
                       "\t\"Save\" any changes that have been staged, storing them into a tree\n\n";
const char *h_status = "\n\ttroll-status - indicate the status of all files in the repo\n\n"
                       "\ttroll status\n\n"
                       "\tThis command is broken, but is meant to display which files are being tracked, which aren't tracked, and which are ready for staging\n\n";
const char *h_log = "\n\ttroll-log\n\n"
                    "\ttroll log\n\n"
                    "\tLists all commits made in the repo\n\n";
const char *h_checkout = "\n\ttroll-checkout\n\n"
                         "\ttroll checkout <tree hash>\n\n"
                         "\tThis command is not yet functioning. Checkout allows the user to visit another commit\n\n"
                         "\tThe hash is the hash provided in things like the log or after a commit\n\n";
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
      else if(!strcmp(argv[1],"add")) {
	printf("%s\n", h_add);
      }
      else if(!strcmp(argv[1],"commit")) {
	printf("%s\n", h_commit);
      }
      else if(!strcmp(argv[1],"ls-files")) {
	printf("%s\n", h_ls_files);
      }
      else if(!strcmp(argv[1],"log")) {
	printf("%s\n", h_log);
      }
      else if(!strcmp(argv[1],"checkout")) {
	printf("%s\n", h_checkout);
      }
      else if(!strcmp(argv[1],"status")) {
	printf("%s\n", h_status);
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
