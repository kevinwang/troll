#include <fcntl.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "object.h"
#include "path.h"

char *hash_object(char *data, int len) {
    /* To debug plaintext */
    /*int i;*/
    /*for (i = 0; i < len; i++) {*/
        /*printf("%d\t%c\n", i, data[i]);*/
    /*}*/

    unsigned char *hash = SHA1((unsigned char *) data, len, NULL);
    char *hex = sha1tohex(hash);

    return hex;
}

char *sha1tohex(unsigned char *hash) {
    char *hex = (char *) malloc(41 * sizeof(char));
    int i;
    for (i = 0; i < 20; i++) {
        sprintf(hex + i * 2, "%02x", hash[i]);
    }
    return hex;
}

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
}
