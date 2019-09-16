#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void testSeq(int * array, size_t n, size_t ans) {
  if (n < 0) {
    printf("The array have a size of negative number.");
    exit(EXIT_FAILURE);
  }

  if (n == 0) {
    printf("The array have a size of 0.");
    if (maxSeq(array, n) != 0) {
      exit(EXIT_FAILURE);
    }
  }

  for (size_t i = 0; i < n; i++) {
    printf("%d", *(array + i));
    if (i < (n - 1)) {
      printf(", ");
    }
  }
  printf("\n");
  size_t an = maxSeq(array, n);
  if (an != ans) {
    printf("Wrong! The answer should be %zu, but you get %zu.\n", ans, an);
    exit(EXIT_FAILURE);
  }
  else {
    printf("Correct. The answer should be %zu.\n", ans);
  }
}

int main(void) {
  size_t n = 10;
  int array1[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  testSeq(array1, n, 4);

  n = 0;
  int array2[4] = {0, 5, 6, 2};
  testSeq(array2, n, 0);

  n = 7;
  int array3[7] = {10, 9, 6, 4, 0, -2, -6};
  testSeq(array3, n, 1);

  n = 13;
  int array4[13] = {3, 6, 7, 24345, -8, -7, -6, -5, -3, 103, 2, 1, 0};
  testSeq(array4, n, 6);

  n = 12;
  int array5[12] = {11, 13, 28, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  testSeq(array5, n, 9);

  n = 12;
  int array6[12] = {3, 3, 3, 3, 1, 1, 1, 1, 1, 0, 0, 0};
  testSeq(array6, n, 1);

  return EXIT_SUCCESS;
}
