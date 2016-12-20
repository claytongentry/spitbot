#include "doctest.h"

#include "word.cpp"

Word w("gravy", "su");

TEST_CASE("initialize member variables") {
  CHECK(w.getVal() == "gravy");
  CHECK(w.getFrequency() == 1);
  CHECK(w.getStressPattern() == "su");

}

TEST_CASE("update frequency") {
  w.incrementFrequency();

  CHECK(w.getFrequency() == 2);
}
