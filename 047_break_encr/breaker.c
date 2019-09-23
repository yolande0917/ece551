#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Find size of chars in file
size_t sizeOfChars(FILE * f) {
  int c;
  size_t n = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      n++;
    }
  }
  if (n == 0) {
    fprintf(stderr, "There is no char in the input file.\n");
    exit(EXIT_FAILURE);
  }
  return n;
}

int findMax(int * array, size_t n) {
  int max = *array;
  int ind = 0;
  for (size_t i = 0; i < n; i++) {
    if (*(array + i) > max) {
      max = *(array + i);
      ind = i;
    }
  }
  return ind;
}

int findMaxFreqIndex(FILE * f, char * chars, int * freq, size_t n) {
  int c;
  int i = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      *(chars + i) = c;
      i++;
    }
  }

  int count = 0;
  char current;
  for (size_t j = 0; j < n; j++) {
    current = *(chars + j);
    count = 0;
    for (size_t k = 0; k <= j; k++) {
      if (*(chars + k) == current) {
        count++;
      }
    }
    *(freq + j) = count;
  }
  // find max index
  int ind = findMax(freq, n);
  return ind;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: break inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open file.\n");
    return EXIT_FAILURE;
  }

  size_t n = sizeOfChars(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file.\n");
    return EXIT_FAILURE;
  }

  char context[n];
  int freq[n];

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Failed to open file.\n");
    return EXIT_FAILURE;
  }

  int maxInd = findMaxFreqIndex(f, context, freq, n);
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file.\n");
    return EXIT_FAILURE;
  }
  char c = context[maxInd];

  // calculate key
  int key = ((c - 'e') + 26) % 26;

  printf("The key is %d.\n", key);
}
