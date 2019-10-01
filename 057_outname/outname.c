#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME

  if (inputName == NULL) {
    fprintf(stderr, "Failed to access the input name.\n");
    exit(EXIT_FAILURE);
  }
  // .counts has 7 chars
  size_t length = strlen(inputName) + 1 + 7;
  // malloc a new string
  char * outName = malloc(length * sizeof(outName));
  // copy
  outName = strcpy(outName, inputName);
  // append .counts
  outName = strcat(outName, ".counts");
  return outName;
}
