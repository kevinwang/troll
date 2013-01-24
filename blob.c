#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "blob.h"
#include "index.h"
#include "object.h"
#include "path.h"

void write_blob(char *filename) {
    /* Open file to hash */
    int fd;
    fd = open(filename, O_RDONLY);
    struct stat buf;
    fstat(fd, &buf);

    char *data = (char *) malloc((size_t) buf.st_size + 15);
    sprintf(data, "blob %lu", (unsigned long) buf.st_size);
    int left_part_len = strlen(data) + 1;
    read(fd, data + left_part_len, buf.st_size);
    int full_len = left_part_len + buf.st_size;

    char *hash = hash_object(data, full_len);

    char *path = get_repo_troll_dir();
    path = (char *) realloc(path, strlen(path) + 49); // Path + "objects/" + 40 digit hash + null terminator
    strcat(path, "objects/");
    strncat(path, hash, 40);

    /* Create object file */
    int objectfd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    write(objectfd, data, full_len);

    /* Add new object to index */
    add_to_index(hash, filename);
}
