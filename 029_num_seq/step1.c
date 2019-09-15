// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return 4 * x - 3;
}

void printSeq1Range(int low, int high) {
  for (int x = low; x < high; x++) {
    printf("%d", seq1(x));
    if (x < (high - 1)) {
      printf(", ");
    }
  }
  printf("\n");
}

int main(void) {
  // Test seq1
  int t = 0;
  printf("seq1(%d) = %d\n", t, seq1(t));
  t = -3;
  printf("seq1(%d) = %d\n", t, seq1(t));
  t = 8;
  printf("seq1(%d) = %d\n", t, seq1(t));
  t = 8024;
  printf("seq1(%d) = %d\n", t, seq1(t));
  t = -1028;
  printf("seq1(%d) = %d\n", t, seq1(t));

  // Test printSeq1range
  int low = 0;
  int high = 4;
  printf("printSeq1range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  low = -2;
  high = 6;
  printf("printSeq1range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  low = 7;
  high = 3;
  printf("printSeq1range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  low = 0;
  high = 0;
  printf("printSeq1range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  low = -79;
  high = 102;
  printf("printSeq1range(%d, %d)\n", low, high);
  printSeq1Range(low, high);

  return EXIT_SUCCESS;
}
