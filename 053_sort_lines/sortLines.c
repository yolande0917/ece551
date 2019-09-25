#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);

  // print data
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
}

size_t readLinesFromFile(char *** lines, FILE * f) {
  size_t i = 0;
  char * curr = NULL;
  size_t linecap = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    *lines = realloc(*lines, (i + 1) * sizeof(**lines));
    (*lines)[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);

  sortData(*lines, i);
  return i;
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f;
  char ** lines = NULL;
  size_t count;
  // read from stdin if argc=1
  if (argc == 1) {
    f = fdopen(0, "r");
    if (f == NULL) {
      fprintf(stderr, "Failed to open the file.\n");
      exit(EXIT_FAILURE);
    }

    // read from the file
    // and sort the lines within the function
    count = readLinesFromFile(&lines, f);
    printf("%lu\n", count);

    // close the file
    if (fclose(f) != 0) {
      fprintf(stderr, "Failed to close the file.\n");
      exit(EXIT_FAILURE);
    }
  }
  else {
    // open file from input file names
    int i = 1;
    while (i < argc) {
      f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Failed to open the file.\n");
        exit(EXIT_FAILURE);
      }

      // read from the file
      // and sort the lines within the function
      count = readLinesFromFile(&lines, f);
      printf("%lu\n", count);

      free(lines);
      lines = NULL;

      // close the file
      if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the file.\n");
        exit(EXIT_FAILURE);
      }
      i++;
    }
  }
  free(lines);
  return EXIT_SUCCESS;
}
