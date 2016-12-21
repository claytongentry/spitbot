#include "doctest.h"

#include "nouncer.cpp"

#define DICTIONARY_FILE "test/support/test_dict.txt"

TEST_SUITE("nouncer");

TEST_CASE("nouncer stores pronunciations correctly") {
  Nouncer n(DICTIONARY_FILE);

  std::vector<std::string> carPhonemes {"K", "AA1", "R"};

  CHECK(n.getSize() == 3);
  CHECK(n.getPhonemes("CAR") == carPhonemes);
  CHECK(n.getNounce("CAR") == "i\"U");

  std::vector<std::string> agoPhonemes {"AH0", "G", "OW1"};
  std::string agoNounce = "bJ*";
  nounceTuple agoPronunciations {agoPhonemes, agoNounce};

  n.insert("AGO", agoPronunciations);

  CHECK(n.getSize() == 4);
  CHECK(n["AGO"] == agoPronunciations);

  CHECK(n.doStressPattern("AGO") == "su");
}

TEST_SUITE_END();
