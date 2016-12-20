#include "doctest.h"

#include "utils.cpp"

TEST_CASE("capitalizes a string"){
  CHECK(Utils::allCaps("test") == "TEST");
  CHECK(Utils::allCaps("TEST") == "TEST");
  CHECK(Utils::allCaps("under_score") == "UNDER_SCORE");
  CHECK(Utils::allCaps("") == "");
}
