/*
 * model.cpp
 * Cameron Matson, Clayton Gentry
*/

#include <iostream>
#include <fstream>

#define LYRICS_FILE "lyrics.txt"

void load_data() {
  std::ifstream fstream;
  fstream.open(LYRICS_FILE);

  if (!fstream.is_open()) {
    throw "Could not load lyrics file";
  }

  fstream.close();
}
