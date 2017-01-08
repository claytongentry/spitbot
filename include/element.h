/* An element the fundamental building block of the matrix class
   Each element contains a primary key and a set of values.
   */
#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>

template <class K, class V>
class Element {
protected:
  K key;
  V value;

public:
  Element();
  Element(K key, V value);

  bool operator==(const Element<K, V>& element);

  ~Element();

  K getKey();
  V getValue();

};

/* Implementation */
template <class K, class V>
Element<K, V>::Element() {
  key = K();
  value = V();
}

template <class K, class V>
Element<K, V>::Element(K key, V value) {
  this->key = key;
  this->value = value;
}

template <class K, class V>
Element<K, V>::~Element() {}

/* element comparison is only on key, not value */
template <class K, class V>
bool Element<K, V>::operator==(const Element<K, V>& element) {
  return (this->key == element.key);
}

template <class K, class V>
K Element<K, V>::getKey() {return key;}

template <class K, class V>
V Element<K, V>::getValue() {return value;}


#endif //ELEMENT_H
