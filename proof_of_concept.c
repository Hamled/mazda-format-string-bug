#include <stdio.h>

#define ARBITRARY_PARAMETER 99 //% Invisible :D

int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Usage: %s <string with format specifications>\n", argv[0]);
  }

  printf(argv[1], ARBITRARY_PARAMETER);
  printf("\n");
  return 0;
}
