#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "commit.h"
#include "object.h"
#include "path.h"
#include "tree.h"

char *write_commit() {
    char *tmpcommit_path = get_repo_troll_dir();
    tmpcommit_path = (char *) realloc(tmpcommit_path, strlen(tmpcommit_path) + 10);
    strcat(tmpcommit_path, "tmpcommit");

    int tmpcommitfd = open(tmpcommit_path, O_RDONLY, 0644);
    free(tmpcommit_path);

    struct stat buf;
    fstat(tmpcommitfd, &buf);

    char *data = (char *) malloc((size_t) buf.st_size + 17);
    sprintf(data, "commit %lu", (unsigned long) buf.st_size);
    int left_part_len = strlen(data) + 1;
    read(tmpcommitfd, data + left_part_len, buf.st_size);
    close(tmpcommitfd);
    int full_len = left_part_len + buf.st_size;

    char *hash = hash_object(data, full_len);

    char *path = get_repo_troll_dir();
    path = (char *) realloc(path, strlen(path) + 49); // Path + "objects/" + 40 digit hash + null terminator
    strcat(path, "objects/");
    strncat(path, hash, 40);

    /* Create object file */
    int objectfd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    write(objectfd, data, full_len);

    return hash;
}

void commit(const char *message) {
    char *tmpcommit_path = get_repo_troll_dir();
    tmpcommit_path = (char *) realloc(tmpcommit_path, strlen(tmpcommit_path) + 10);
    strcat(tmpcommit_path, "tmpcommit");
    char *treehash = write_tree();

    int tmpcommitfd = open(tmpcommit_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    free(tmpcommit_path);

    write(tmpcommitfd, "tree ", 5);
    write(tmpcommitfd, treehash, 40);

    char *path = get_repo_troll_dir();
    path = (char *) realloc(path, strlen(path) + 7);
    strcat(path, "master");
    int masterfd = open(path, O_CREAT | O_RDWR, 0644);
    struct stat buf;
    fstat(masterfd, &buf);
    if (buf.st_size > 0) {
        write(tmpcommitfd, "\nparent ", 8);
        char *parenthash = (char *) malloc(41 * sizeof(char));
        read(masterfd, parenthash, 40);
        write(tmpcommitfd, parenthash, 40);
    }

    write(tmpcommitfd, "\nauthor ", 8);
    write(tmpcommitfd, getenv("USER"), strlen(getenv("USER")));
    write(tmpcommitfd, "\n\n", 2);
    write(tmpcommitfd, message, strlen(message));
    write(tmpcommitfd, "\n", 1);

    close(tmpcommitfd);

    char *hash = write_commit();

    /* Update master ref */
    lseek(masterfd, 0, SEEK_SET);
    write(masterfd, hash, 40);

    char *headpath = get_repo_troll_dir();
    headpath = (char *) realloc(headpath, strlen(path) + 5);
    strcat(headpath, "HEAD");
    int headfd = open(headpath, O_CREAT | O_RDWR, 0644);
    struct stat headbuf;
    fstat(headfd, &headbuf);
    if (headbuf.st_size == 0) {
        write(headfd, "master", 6);
    }

    printf("[master %.7s] %s\n", hash, message);
}

char *get_parent(char *hash) {
    char *obj_path = get_repo_troll_dir();
    obj_path = (char *) realloc(obj_path, strlen(obj_path) + 49);
    strcat(obj_path, "objects/");
    strncat(obj_path, hash, 40);

    int objectfd = open(obj_path, O_RDONLY);
    if (errno == ENOENT) {
        printf("fatal: Object does not exist.\n");
        exit(128);
    }

    struct stat buf;
    fstat(objectfd, &buf);

    char *data = (char *) malloc((size_t) buf.st_size + 1);
    read(objectfd, data, buf.st_size);
    char *data_right = data + strlen(data) + 1;

    char *parent_hash = strstr(data_right, "parent");
    if (parent_hash) {
        parent_hash += 7;
        char *hashcpy = (char *) malloc(41 * sizeof(char));
        strncpy(hashcpy, parent_hash, 40);
        free(data);
        return hashcpy;
    }

    free(data);
    return NULL;
}
