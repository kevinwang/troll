#include <fcntl.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "object.h"

char *hash_and_write_object(char *data) {
    return NULL;
}

char *write_blob(char *filename) {
    int fd;
    fd = open(filename, O_RDONLY);
    struct stat buf;
    fstat(fd, &buf);
    char *data = (char *) malloc((size_t) buf.st_size + 15);
    sprintf(data, "blob %lu\0", (unsigned long) buf.st_size);
    printf("%s\n", data);
    int full_len = strlen(data) + 1;
    printf("full_len: %d\n", full_len);
    read(fd, data + full_len + 1, buf.st_size);
    printf("%s\0%s", data, data + full_len + 1);
    return NULL;
}
