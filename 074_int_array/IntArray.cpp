#include "IntArray.h"

#include <assert.h>

#include <cstdlib>
#include <ostream>
IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.size()]),
    numElements(rhs.size()) {
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.size()];
    for (int i = 0; i < rhs.size(); i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.size();
    data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements);
  const int & ref = data[index];
  return ref;
}
int & IntArray::operator[](int index) {
  assert(index < numElements);
  int & ref = data[index];
  return ref;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (rhs.size() != numElements) {
    return false;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  int n = rhs.size();
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      s << rhs[i];
      if (i < n - 1) {
        s << ", ";
      }
    }
  }
  s << "}";
  return s;
}
