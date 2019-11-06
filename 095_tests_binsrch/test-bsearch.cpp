#include <stdio.h>

#include <cassert>
#include <cmath>
#include <cstdlib>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SimpleFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned n;
  if (high > low) {
    n = std::log(high - low) / std::log(2);
  }
  else {
    n = 1;
  }

  CountedIntFn c = CountedIntFn(n, f, mesg);
  int ans = binarySearchForZero(&c, low, high);
  assert(ans == expected_ans);

  //  c.invoke(int arg)
}

int main(void) {
  SimpleFunction f;
  check(&f, -1, 1, 0, "SimpleFunction");
  check(&f, 6, 6, 6, "SimpleFunction");
  check(&f, 6, 7, 6, "SimpleFunction");
  check(&f, -12, -6, -7, "SimpleFunction");
  check(&f, -12, 3, 0, "SimpleFunction");
  check(&f, -1, 4, 0, "SimpleFunction");
  check(&f, 0, 5, 0, "SimpleFunction");

  SinFunction s;
  check(&s, 0, 150000, 52359, "SinFunction");
  //check(&s, 60000, 150000, 60000, "SinFunction");
  //check(&s, 0, 40000, 39999, "SinFunction");
  // check(&s, 0, 150000, 52359, "SinFunction");
  //check(&s, 0, 150000, 52359, "SinFunction");
  //check(&s, 0, 150000, 52359, "SinFunction");

  return EXIT_SUCCESS;
}
