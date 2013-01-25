#ifndef COMMIT_H

#define COMMIT_H

char *write_commit();
void commit(const char *message);
char *get_parent(char *hash);

#endif /* end of include guard: COMMIT_H */
