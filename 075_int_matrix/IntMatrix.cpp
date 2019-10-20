#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.getRows()),
    numColumns(rhs.getColumns()),
    rows(new IntArray *[rhs.getRows()]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
    *(rows[i]) = rhs[i];
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    int r = rhs.getRows();
    int c = rhs.getColumns();
    IntArray ** temp = new IntArray *[r];
    for (int i = 0; i < r; i++) {
      temp[i] = new IntArray(c);
      *(temp[i]) = rhs[i];
    }

    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    rows = temp;
    numRows = r;
    numColumns = c;
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  const IntArray & a = *(rows[index]);
  return a;
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  IntArray & a = *(rows[index]);
  return a;
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  int r = rhs.getRows();
  int c = rhs.getColumns();
  if (r != numRows || c != numColumns) {
    return false;
  }
  for (int i = 0; i < r; i++) {
    if (*(rows[i]) != rhs[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(rhs.getRows() == numRows);
  assert(rhs.getColumns() == numColumns);
  IntMatrix m = IntMatrix(rhs);

  for (int i = 0; i < numRows; i++) {
    IntArray & a = m[i];
    IntArray & thisrow = *(rows[i]);
    for (int j = 0; j < numColumns; j++) {
      a[j] += thisrow[j];
    }
  }
  return m;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  int r = rhs.getRows();
  if (r > 0) {
    for (int i = 0; i < r; i++) {
      s << rhs[i];
      if (i < r - 1) {
        s << ",\n";
      }
    }
  }
  s << " ]";
  return s;
}
