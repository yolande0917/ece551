

#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  char * array = "hello";
  std::string s(array);
  // array = s.c_str();
  //strcpy(array, s.c_str());
  // for (int i = 0; i < n; i++) {
  //  std::cout << array[i];
  // }
  std::cout << s << "\n";
  return 0;
}
