#include "doctest.h"

#include "word.cpp"

TEST_CASE("basic operations") {
  Word w("gravy","su");

  CHECK(w.getVal() == "gravy");
  CHECK(w.getFrequency() == 1);
  CHECK(w.getStressPattern() == "su");

}

TEST_CASE("update frequency") {
  Word w("gravy", "su");

  w.incrementFrequency();

  CHECK(w.getFrequency() == 2);
}
