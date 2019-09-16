// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  int x0 = -2;
  int y0 = 3;
  int dx = x - x0;
  int dy = y - y0;
  return 6 + dx * dy;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int count = 0;
  if (xHi <= xLow || yHi <= yLow) {
    return 0;
  }
  int current;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      current = seq3(i, j);
      if (current % 2 == 0) {
        count++;
      }
    }
  }
  return count;
}

int main(void) {
  // Test seq3
  int x = -2;
  int y = 18;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = -9;
  y = 3;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = -4;
  y = -5;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = 5;
  y = 2;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = -3;
  y = -4;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = 3;
  y = 4;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  x = -5;
  y = 5;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test countEveninseq3range
  int xLow = 0;
  int xHi = 2;
  int yLow = 0;
  int yHi = 3;
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = 3;
  xHi = 3;
  yLow = -2;
  yHi = 4;
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = 1;
  xHi = 3;
  yLow = 4;
  yHi = -2;
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = -5;
  xHi = -4;
  yLow = -5;
  yHi = -4;
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = -1;
  xHi = 3;
  yLow = -3;
  yHi = 1;
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  xLow = 0;
  xHi = 4;
  yLow = 0;
  yHi = 4;
  printf("countEvenInSeq3range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  return EXIT_SUCCESS;
}
