/* Matrix is an abstract data structure that is a vector of vectors
   The outer vector consists of a data element indicating the row, and a
   vector of values representing the columns of the matrix.
   Each inner vector is a row of equal length to the outer vector,
   meaning that the matrix is square.  The elements of the outer and inner
   vector have a primary key, and a set of values.  Both vectors can be sorted
   by any value in the data element.
   */

#ifndef MATRIX_H
#define MATRIX_H

#include "row.h"

template<class T>
class Matrix {
protected:
    std::vector<Row<T>> rows;

public:
  Matrix();
  ~Matrix();

  Row<T>& operator[](size_t i);

};

// Implementation

template <class T>
Matrix<T>::Matrix() {
  rows = std::vector<Row<T>>(1);
}

template <class T>
Matrix<T>::~Matrix() {}

template <class T>
Row<T>& Matrix<T>::operator[](size_t i) {
  return rows.at(i);
}


#endif //MATRIX_H
