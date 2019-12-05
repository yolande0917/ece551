#include <signal.h>

#include <cstdlib>
#include <iostream>

int main(void) {
  signal(5, SIG_DFL);
  std::cout << "Sending signal 5.\n";
  raise(5);
  return EXIT_SUCCESS;
}
