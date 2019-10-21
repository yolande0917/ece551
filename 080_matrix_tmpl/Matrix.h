#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]) {
    for (int i = 0; i < r; i++) {
      rows[i] = new std::vector<T>(c);
    }
  }
  Matrix(const Matrix & rhs) :
      numRows(rhs.getRows()),
      numColumns(rhs.getColumns()),
      rows(new std::vector<T> *[rhs.getRows()]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
      *(rows[i]) = rhs[i];
    }
  }
  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      int r = rhs.getRows();
      int c = rhs.getColumns();
      std::vector<T> ** temp = new std::vector<T> *[r];
      for (int i = 0; i < r; i++) {
        temp[i] = new std::vector<T>(c);
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

  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    std::vector<T> & v = *(rows[index]);
    return v;
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    std::vector<T> & v = *(rows[index]);
    return v;
  }

  bool operator==(const Matrix & rhs) const {
    int r = rhs.getRows();
    int c = rhs.getColumns();
    if (r != numRows || c != numColumns) {
      return false;
    }
    for (int i = 0; i < r; i++) {
      if (*rows[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert(rhs.getRows() == numRows);
    assert(rhs.getColumns() == numColumns);
    Matrix m = Matrix(*this);

    for (int i = 0; i < numRows; i++) {
      std::vector<T> & v = m[i];
      std::vector<T> thisrow = rhs[i];
      for (int j = 0; j < numColumns; j++) {
        v[j] += thisrow[j];
      }
    }
    return m;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    if (i > 0) {
      s << ",\n";
    }
    // print vector
    std::vector<T> v = rhs[i];
    typename std::vector<T>::iterator it = v.begin();
    s << "{";
    while (it != v.end()) {
      s << *it;
      if (it < v.end() - 1) {
        s << ", ";
      }
      ++it;
    }
    s << "}";
  }

  s << " ]";
  return s;
}

#endif
