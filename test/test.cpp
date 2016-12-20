#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "word.h"
#include "utils.h"
#include "utils.cpp"
#include "word.cpp"

TEST_CASE("lookin at word"){
  Word w("gravy", "su");

  CHECK(w.getVal() == "gravy");
  CHECK(w.getFrequency() == 1);

  w.incrementFrequency();
  CHECK(w.getFrequency() == 2);

  CHECK(w.getStressPattern() == "su");

  Word v("gravy", "su");
  Word x("notgravy", "suu");

  // CHECK(w == v);
  // CHECK(!(w == x));

}
