#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open the input file.\n");
    exit(EXIT_FAILURE);
  }

  int count = 0;
  char line[12];

  char matrix[10][10];
  while (fgets(line, 12, f) != NULL) {
    if (strchr(line, '\n') == NULL) {  // check \n in each line
      fprintf(stderr, "One or more lines are too long.\n");
      exit(EXIT_FAILURE);
    }
    if ((strchr(line, '\0') - line) < 11) {  // check \0 in each line
      fprintf(stderr, "One or more lines are too short.\n");
      fprintf(stderr, "%d\n", (int)(strchr(line, '\0') - line));
      exit(EXIT_FAILURE);
    }
    count++;
    if (count > 10) {
      fprintf(stderr, "Too many lines.\n");
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 10; i++) {
      matrix[i][10 - count] = line[i];
    }
  }
  if (count < 10) {
    fprintf(stderr, "Too few lines.\n");
    exit(EXIT_FAILURE);
  }

  if (fclose(f) != 0) {
    fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
    exit(EXIT_FAILURE);
  }

  for (int j = 0; j < 10; j++) {
    for (int k = 0; k < 10; k++) {
      printf("%c", matrix[j][k]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
