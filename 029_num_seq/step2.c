// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  if (x % 4 == 2 || x % 4 == -2) {
    return 2 * x;
  }
  return (x + 3) * x + 1;
}

int sumSeq2(int low, int high) {
  int total = 0;
  for (int i = low; i < high; i++) {
    total += seq2(i);
  }
  return total;
}

int main(void) {
  // Test seq2
  int x = 0;
  printf("seq2(%d) = %d\n", x, seq2(x));
  x = 6;
  printf("seq2(%d) = %d\n", x, seq2(x));
  x = 11;
  printf("seq2(%d) = %d\n", x, seq2(x));
  x = -4;
  printf("seq2(%d) = %d\n", x, seq2(x));
  x = -2;
  printf("seq2(%d) = %d\n", x, seq2(x));
  x = 13;
  printf("seq2(%d) = %d\n", x, seq2(x));
  x = 12;
  printf("seq2(%d) = %d\n", x, seq2(x));
  x = -1;
  printf("seq2(%d) = %d\n", x, seq2(x));

  // Test sumSeq2
  int low = 0;
  int high = 2;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  low = 3;
  high = 6;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  low = 9;
  high = 7;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  low = -3;
  high = -3;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  low = -4;
  high = 15;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));

  return EXIT_SUCCESS;
}
