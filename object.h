#ifndef OBJECT_H

#define OBJECT_H

#define OBJ_COMMIT 1
#define OBJ_TREE 2
#define OBJ_BLOB 3

char *hash_object(char *data, int len);
char *sha1tohex(unsigned char *hash);
void write_blob(char *filename);

#endif /* end of include guard: OBJECT_H */
