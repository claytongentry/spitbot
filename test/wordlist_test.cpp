#include "doctest.h"


#include "wordList.cpp"


TEST_SUITE("wordlist");

TEST_CASE("constructor") {
  Word w("gravy", "su");
  Word n("_NULL_", "");

  WordList l(w);

  CHECK( (l.getBase() == w) );
  CHECK( l.getSize() == 1 );
  CHECK( (l.getLeaders().at(0) == n) );
}

TEST_CASE("add leader") {
  Word w("gravy", "su");
  Word x("boat", "s");
  Word y("train", "s");

  WordList l(w);

  l.addLeader(x);

  CHECK( l.getSize() == 2);
  CHECK( (l.getLeaders().at(1) == x));

  l.addLeader(y);

  CHECK( l.getSize() == 3);
  CHECK( (l.getLeaders().at(2) == y));
}

TEST_CASE("pick leader") {
  Word w("gravy", "su");

  WordList l(w);

  CHECK(l.pickLeader()->getVal() == "_NULL_");
  CHECK_FALSE(l.pickLeader()->getVal() == "gravy");
}


TEST_SUITE_END();
