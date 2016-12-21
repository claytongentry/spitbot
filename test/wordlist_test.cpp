#include "doctest.h"


#include "wordList.cpp"


TEST_SUITE("wordlist");

TEST_CASE("constructor") {
  Word w("gravy", "su");
  Word n("_NULL_", "");

  WordList l(w);

  CHECK( (l.getBase() == w) == true );
  CHECK( l.getLeaders().size() == 1 );
  CHECK( (l.getLeaders().at(0) == n) == true );
}

TEST_CASE("add leader") {
  Word w("gravy", "su");
  Word x("boat", "s");
  Word y("train", "s");

  WordList l(w);

  l.addLeader(x);

  CHECK( l.getLeaders().size() == 2);
  CHECK( (l.getLeaders().at(1) == x) == true );

  l.addLeader(y);

  CHECK( l.getLeaders().size() == 3);
  CHECK( (l.getLeaders().at(2) == y) == true );
}

TEST_CASE("pick leader") {
  Word w("gravy", "su");

  WordList l(w);
}


TEST_SUITE_END();
