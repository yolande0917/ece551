#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t max = 1;
  size_t num = 1;
  // int * p = array;
  int previous = *array;
  for (size_t i = 1; i < n; i++) {
    if (*(array + i) > previous) {
      num++;
    }
    else {
      num = 1;
    }
    previous = *(array + i);
    if (num > max) {
      max = num;
    }
  }
  return max;
}
