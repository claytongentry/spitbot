#include "doctest.h"

#include "denouncer.cpp"

TEST_SUITE("denouncer");

TEST_CASE("add nounce") {
  Denouncer d;

  CHECK(d.getSize() == 0);
  d.addNounce("A3i", "somethin");
  CHECK(d.getSize() == 1);
}

TEST_SUITE_END();
