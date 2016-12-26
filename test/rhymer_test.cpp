#include "doctest.h"

#include <iostream>
#include "denouncer.h"
#include "nouncer.h"
#include "rhymer.cpp"

#define DICTIONARY_FILE "test/support/test_dict.txt"

TEST_SUITE("rhymer");

TEST_CASE("rhyme") {
  Nouncer n(DICTIONARY_FILE);
  Denouncer d;
  d.addNounce("l&K", "cat");
  d.addNounce("QX+W", "money");

  Rhymer r(&n, &d);
  CHECK((r.rhyme("honey") == "money"));

}

TEST_SUITE_END();
