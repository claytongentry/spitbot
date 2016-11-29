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

#include "battle.h"
#include "model.h"
#include "nouncer.h"
#include "utils.h"
#include "word.h"
#include "wordList.h"

#define LYRICS_FILE "lyrics/lyrics.txt"
#define TEST_FILE   "lyrics/test.txt"

/*
 * Parses a line
 *
 * Each new unique word is appended to the adjacency list
 * as a base word, and its preceding word is instantiated
 * as a node in its leaders vector. If the leader has already
 * been instantiated, its frequency is updated.
 *
 * Lines are processed individually to ensure the model
 * doesn't assume false positive adjacency between the
 * last word of a preceding line and the first word of
 * its successor.
 */
void parseLine(std::string in, Model* model) {
  std::istringstream ss(Utils::flip(in));
  std::string temp;
  std::string pronunciation;

  Word* current = nullptr;
  Word* leader  = nullptr;

  // TODO: Make this not spaghetti.
  while (ss >> temp) {
    // pronunciation = Nouncer::lookup(temp);
    // Denouncer::addWord(temp, pronunciation)

    current = new Word(temp);
    model->addOrUpdate(current);

    // if first word on (reversed) line
    if (leader == nullptr) {
      leader = current;
    }
    else {
      WordList* list_ptr = model -> find(leader);

      if (list_ptr != nullptr) {
        (*list_ptr).add_leader(*current);
        leader = current;
      }
      else {
        std::cerr << "Could not get leader." << std::endl;
      }
    }
  }
}

void rap(std::string bar, Model* model, Nouncer* pd) {
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
  Model* model = new Model();

  std::string line;
  std::ifstream file(LYRICS_FILE);

  if (file) {
    while(getline(file, line)) {
      parseLine(line, model);
    }

    file.close();
  }
  else {
    std::cerr << "Could not load lyrics file" << std::endl;
  }

  std::cout << "Model ready!" << std::endl;

  // std::cout << "Thinking about rhymes..." << std::endl;
  // Nouncer* pd = new Nouncer();
  // std::cout << "Rhyme dictionary ready!" << std::endl;

  // std::string bar;
  // std::cout << "Gimme a bar\n";
  // std::getline(std::cin, bar);
  //
  // rap(bar, model, pd);
}
