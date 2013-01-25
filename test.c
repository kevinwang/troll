#include <stdio.h>
#include "index.h"

int main(int argc, const char *argv[])
{
  printf("Returns 0: %d\n", index_file_check("cc628ccd10742baea8241c5924df992b5c019f71","blah"));
  printf("Returns +: %d\n", index_file_check("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","world"));
  printf("Returns -1: %d\n", index_file_check("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","blah"));
    return 0;
}
