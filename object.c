#include <errno.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int print_object(char *hash) {
    char *obj_path = get_repo_troll_dir();
    obj_path = (char *) realloc(obj_path, strlen(obj_path) + 49);
    strcat(obj_path, "objects/");
    strncat(obj_path, hash, 40);

    FILE *f = fopen(obj_path, "r");
    if (errno == ENOENT) {
        printf("fatal: Object does not exist.\n");
        exit(128);
    }

    char c;
    while (fgetc(f) != '\0');
    while ((c = fgetc(f)) != EOF) printf("%c", c);
    return 0;
}
