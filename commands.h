#ifndef COMMANDS_H

#define COMMANDS_H

int cmd_help(int argc, const char *argv[]);
int cmd_init(int argc, const char *argv[]);
int cmd_face(int argc, const char *argv[]);
int cmd_add(int argc, const char *argv[]);
int cmd_ls_files(int argc, const char *argv[]);
int cmd_status(int argc, const char *argv[]);
int cmd_commit(int argc, const char *argv[]);
int cmd_log(int argc, const char *argv[]);

#endif /* end of include guard: COMMANDS_H */
