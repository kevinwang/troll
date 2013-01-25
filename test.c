#include <stdio.h>
#include "commit.h"
#include "tree.h"

int main(int argc, const char *argv[])
{
    printf("%s\n", get_parent("01635e50447ba33bfc65ea7dea3fd8ccac36142d"));
    /*get_parent("01635e50447ba33bfc65ea7dea3fd8ccac36142d");*/
    return 0;
}
