#include <signal.h>

#include <cstdlib>
#include <iostream>

int main(void) {
  signal(SIGTERM, SIG_DFL);
  std::cout << "Sending signal " << SIGTERM << ".\n";
  raise(SIGTERM);
  return EXIT_SUCCESS;
}
