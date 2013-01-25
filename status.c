#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include "commands.h"
#include "path.h"
#include "index.h"

int cmd_status(int argc, const char *argv[]) {
    die_if_not_troll_repo();
    char *currdir = getcwd();
    char *trollpath = get_repo_troll_dir();
    char *usta = (char *)malloc(strlen(trollpath) + 12);
    strcat(usta, trollpath);
    strcat(usta, "unstaged.tmp");
    char *utra = (char *)malloc(strlen(trollpath) + 13);
    strcat(utra, trollpath);
    strcat(utra, "untracked.tmp");
    int unstaged = open(usta,O_RDWR);
    int untracked = open(utra,O_RDWR);

    char *repo_path = (char *) malloc(strlen(trollpath) - 7);
    strncat(repo_path,trollpath,strlen(trollpath) - 7);
    printf("%s %s %s\n",repo_path,usta,utra);
    free(usta);
    free(utra);
    search_dirs(unstaged, untracked, trollpath);
    //print both files here
    
    chdir(currdir);
    close(unstaged);
    close(untracked);
    unlink("unstaged.tmp");
    unlink("untracked.tmp");    
    return 0;
}

void search_dirs(int unstaged, int untracked, char *curr) {

}
