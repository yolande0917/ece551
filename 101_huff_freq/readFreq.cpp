#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f;
  f.open(fname);
  if (!f.good()) {
    std::cerr << "Can't open the file.\n";
    exit(EXIT_FAILURE);
  }

  uint64_t * freq = new uint64_t[257];
  for (int i = 0; i < 257; i++) {
    freq[i] = 0;
  }
  int c;
  while ((c = f.get()) >= 0) {
    freq[c] += 1;
  }
  freq[256] += 1;

  f.close();
  return freq;
}
