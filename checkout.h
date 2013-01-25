#ifndef CHECKOUT_H
#define CHECKOUT_H

int cmd_checkout(int argc, const char *argv[]);
void new_index(char *hash);
void copy_out();

#endif
