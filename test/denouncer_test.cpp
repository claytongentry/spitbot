#include "doctest.h"

#include "denouncer.cpp"

TEST_SUITE("denouncer");

Denouncer d;
TEST_CASE("add nounce") {
  CHECK(d.getSize() == 0);
  d.addNounce("l&K", "cat");
  CHECK(d.getSize() == 1);
}

TEST_CASE("get index") {
  CHECK(d.getIndex("l&K") == 0);  //cat

  d.addNounce("QX+W", "money");

  CHECK(d.getIndex("l&K") == 1);  //cat
  CHECK(d.getIndex("QX+W") == 0); //money
  CHECK(d.getIndex("QX+K") == 0); //honey

}

TEST_CASE("lookup") {
  CHECK(d.lookUp(0) == "money");
  CHECK(d.lookUp(1) == "cat");
  CHECK(d.lookUp(2) == "_0");
  CHECK(d.lookUp(-1) == "_0");
}

TEST_SUITE_END();
