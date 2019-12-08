#include <cstdlib>
#include <iostream>

int main(int argc, char ** argv) {
  std::cout << "Print out arguments:\n";
  for (int i = 0; i < argc; i++) {
    std::cout << "Argument " << (i + 1) << ": ";
    std::cout << argv[i] << std::endl;
  }
  return EXIT_SUCCESS;
}
