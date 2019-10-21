#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

template<typename T>
void sortAndPrint(std::vector<T> v) {
  std::sort(v.begin(), v.end());
  typename std::vector<T>::iterator it = v.begin();
  while (it != v.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  std::vector<std::string> v;
  std::string s;
  if (argc == 1) {
    // read from std::cin
    while (std::getline(std::cin, s)) {
      // std::cin >> s;
      v.push_back(s);
      s.clear();
    }
    // sort and print vector
    sortAndPrint(v);
    v.clear();
  }
  else {
    // read from files std::ifstreams

    for (int i = 1; i < argc; i++) {
      std::ifstream file;
      file.open(argv[i]);
      if (!file.good()) {
        std::cerr << "Invalid file name!" << std::endl;
        exit(EXIT_FAILURE);
      }
      // while (file.good()){
      //file.getline(s);
      // }
      while (std::getline(file, s)) {
        // file >> s;
        v.push_back(s);
        s.clear();
      }
      file.close();
      //      if (file.failbit != 0) {
      //std::cout << "Invalid file name!" << std::endl;
      // exit(EXIT_FAILURE);
      //}
      // sort and print vector
      sortAndPrint(v);
      v.clear();
    }
  }

  return EXIT_SUCCESS;
}
