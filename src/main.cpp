/*
 * JeezyAI is a rap bot that emulates Young Jeezy.
 *
 * Given a bar, JeezyAI will return a rhyme on beat. The AI is trained on a
 * bank of Jeezy lyrics, so it spits like Jeezy.
 *
 * Cameron Matson, Clayton Gentry
 */

#include <iostream>
#include <fstream>
#include <string>

#include "model.h"
#include "word.h"
#include "wordList.h"
#include "battle.h"
#include "phonemeDict.h"

#define LYRICS_FILE "lyrics/lyrics.txt"
#define TEST_FILE "lyrics/test.txt"

void rap(std::string bar, Model* model, PhonemeDict* pd) {
  if (bar == "exit") {
    return;
  }
  else {
    Battle* battle = new Battle(bar, model, pd);
    battle -> spit();

    std::getline(std::cin, bar);
    rap(bar, model, pd);
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Initializing model..." << std::endl;
  Model* model = new Model(LYRICS_FILE);
  std::cout << "Model ready!" << std::endl;

  std::cout << "Thinking about rhymes..." << std::endl;
  PhonemeDict* pd = new PhonemeDict();
  std::cout << "Rhyme dictionary ready!" << std::endl;

  std::string bar;
  std::cout << "Gimme a bar\n";
  std::getline(std::cin, bar);

  rap(bar, model, pd);
}
