#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if ((high - low) <= 1) {
    return low;
  }
  int middle = (high + low) / 2;
  int v = f->invoke(middle);
  if (v > 0) {
    return binarySearchForZero(f, low, middle);
  }
  else {
    return binarySearchForZero(f, middle, high);
  }
}
