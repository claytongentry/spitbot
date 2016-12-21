#include "doctest.h"

#include "word.cpp"


TEST_CASE("initialize member variables") {
  Word w("gravy", "su");
  CHECK(w.getVal() == "gravy");
  CHECK(w.getFrequency() == 1);
  CHECK(w.getStressPattern() == "su");
}

TEST_CASE("copy constructor") {
  Word w("gravy", "su");

  Word x = w;

  CHECK(x.getVal() == "gravy");
  CHECK(x.getFrequency() == 1);
  CHECK(w.getStressPattern() == "su");

  CHECK(&w != &x);
}

TEST_CASE("update frequency") {
  Word w("gravy", "su");
  w.incrementFrequency();

  CHECK(w.getFrequency() == 2);
}

TEST_CASE("comparison operator") {
  Word w("gravy", "su");
  Word x("gravy", "su");

  Word y("gravy", "uu");

  Word z("notgravy", "su");
  Word u("notgravy", "uu");

  CHECK((w==x));
  CHECK((w==y));
  CHECK_FALSE((w==z));
  CHECK_FALSE((w==u));
}
