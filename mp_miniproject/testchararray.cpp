#include <bits/stdc++.h>

#include <cstdlib>
#include <iostream>
#include <string>

int main() {
  std::string s = "hey";

  int n = s.length();
  char array[n + 1];
  strcpy(array, s.c_str());
  for (int i = 0; i < n; i++) {
    std::cout << array[i];
  }
  return 0;
}
