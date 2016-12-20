#include "doctest.h"

#include "utils.cpp"

TEST_CASE("capitalizes a string") {
  CHECK(Utils::allCaps("test") == "TEST");
  CHECK(Utils::allCaps("TEST") == "TEST");
  CHECK(Utils::allCaps("under_score") == "UNDER_SCORE");
  CHECK(Utils::allCaps("") == "");
}

TEST_CASE("downcases a string") {
  CHECK(Utils::noCaps("TEST") == "test");
  CHECK(Utils::noCaps("test") == "test");
  CHECK(Utils::noCaps("UNDER_SCORE") == "under_score");
  CHECK(Utils::noCaps("") == "");
}

TEST_CASE("removes punctuation from string") {
  CHECK(Utils::removePunc("google.com") == "googlecom");
  CHECK(Utils::removePunc("*&!((.#))") == "");
  CHECK(Utils::removePunc("hello world") == "hello world");
}

TEST_CASE("flips a string") {
  CHECK(Utils::flip("goof ball") == "ball goof");
  CHECK(Utils::flip("foo") == "foo");
  CHECK(Utils::flip("Foo bar baz.") == "baz bar Foo.");
}

TEST_CASE("excludes a number from a range") {
  CHECK(Utils::randInRangeExclude(1, 2, 2) == 1);
  CHECK(Utils::randInRangeExclude(1, 0, 0) == 1);
  CHECK(Utils::randInRangeExclude(1, 1, 1) == NULL);
}
