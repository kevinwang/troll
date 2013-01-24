#include <stdio.h>
#include "object.h"

int main(int argc, const char *argv[])
{
    char hash1[] = "0883090d16fadf77b60f1ae2bd3fccacfce92425";
    char hash2[] = "1883090d16fadf77b60f1ae2bd3fccacfce92425";

    printf("Retrieving object %s\n", hash1);
    print_object("0883090d16fadf77b60f1ae2bd3fccacfce92425");

    printf("Retrieving object %s\n", hash2);
    print_object("1883090d16fadf77b60f1ae2bd3fccacfce92425");

    return 0;
}
