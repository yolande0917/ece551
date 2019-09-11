#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (x < 0 || y < 0) {
    printf("No negative number for x or y!");
    exit(EXIT_FAILURE);
  }
  if (sizeof(x) != sizeof(expected_ans) || sizeof(y) != sizeof(expected_ans)) {
    printf("Wrong input type for x or y!");
    exit(EXIT_FAILURE);
  }

  unsigned ans = power(x, y);

  if (expected_ans != ans) {
    printf("Wrong! The expected answer of power(%u, %u) is %u, but you get %u.\n",
           x,
           y,
           expected_ans,
           ans);
    exit(EXIT_FAILURE);
  }
  else {
    printf("Correct. The expected answer of power(%u, %u) is %u, and you get %u.\n",
           x,
           y,
           expected_ans,
           ans);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(4294967294, 1, 4294967294);
  run_check(1, 6, 1);
  run_check(2, 0, 1);
  run_check(3, 4294967295, 2863311531);
  run_check(10, 2, 100);
  // run_check('c', 1, 0);
  // run_check(4, 'n', 0);

  return EXIT_SUCCESS;
}
