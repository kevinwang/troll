#ifndef OBJECT_H

#define OBJECT_H

#define OBJ_COMMIT 1
#define OBJ_TREE 2
#define OBJ_BLOB 3

char *hash_object(int type, char *data);
char *write_blob(int fd, char *filename);

#endif /* end of include guard: OBJECT_H */
