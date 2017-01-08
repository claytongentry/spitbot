/* A Row object represents a row in the matrix.
   A Row has two members, a primary element, and a vector
   of associated elements.  The values of the elements in the
   vector are dependent on primary element of that row.
   */
#ifndef ROW_H
#define ROW_H

#include <vector>

#include "element.h"

template <class T>
class Row {
protected:
  T primary;
  std::vector<T> columns;

public:
  Row ();
  Row (T element);

  ~Row ();

  //returns the primary element of the row
  T getPrimary();

  //returns the column vector
  std::vector<T> getColumns() ;

  /*reutrns the element at the given index i, throws
  OUT_OF_BOUNDS exception if index is not valid*/
  T& operator[](size_t i);

  /* Attempts to and an element to the row.
  Returns the position of the element inserted into the
  row, if the element is found returns its current position.
  If the given element is the primary returns -1. */
  int addElement(T element);
};

// Implementation

template <class T>
Row<T>::Row() {
  columns = std::vector<T>(1);
}

template <class T>
Row<T>::Row(T element) {
  primary = element;
}

template <class T>
Row<T>::~Row () {}

template <class T>
T Row<T>::getPrimary() {
  return primary;
}

template <class T>
std::vector<T> Row<T>::getColumns() {
  return columns;
}

template <class T>
T& Row<T>::operator[](size_t i) {
  return columns.at(i);
}

template <class T>
int Row<T>::addElement(T element) {
  if (primary == element) return -1;

  int index = 0;
  for (; index < columns.size(); index++)
    if (columns[index] == element) break;

  if (index != columns.size()) return index;

  columns.push_back(element);
  return index;
}


#endif //ROW_H
