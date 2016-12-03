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
#include "denouncer.h"
#include "model.h"
#include "nouncer.h"
#include "utils.h"
#include "word.h"
#include "wordList.h"

#define LYRICS_FILE "lyrics/lyrics.txt"
#define TEST_FILE   "lyrics/test.txt"

void rap(std::string bar, Model* model, Nouncer* nouncer, Denouncer* denouncer);
void parseFile(std::string filename, Model* model, Nouncer* nouncer, Denouncer* denouncer);
void parseLine(std::string in, Model* model, Nouncer* nouncer, Denouncer* denouncer);

int main(int argc, char *argv[]) {
  Model* model         = new Model();
  Nouncer* nouncer     = new Nouncer();
  Denouncer* denouncer = new Denouncer();

  parseFile(LYRICS_FILE, model, nouncer, denouncer);

  std::string bar;
  std::cout << "Gimme a bar" << std::endl;
  std::getline(std::cin, bar);

  rap(bar, model, nouncer, denouncer);
}

/*
 * Defines the recursive functionality to consume a given bar and respond.
 */
void rap(std::string bar, Model* model, Nouncer* nouncer, Denouncer* denouncer) {
  if (bar == "exit") {
    return;
  }
  else {
    Battle* battle = new Battle(bar, model, nouncer, denouncer);
    battle->spit();

    std::getline(std::cin, bar);
    rap(bar, model, nouncer, denouncer);
  }
}

/*
 * Parses a text file of lyrics
 *
 * Iterates through each line of the file, passing references to
 * the data structures to be constructed during analysis.
 */
void parseFile(std::string filename, Model* model, Nouncer* nouncer, Denouncer* denouncer) {
  std::string line;
  std::ifstream file(filename);

  if (file) {
    while(getline(file, line)) {
      parseLine(line, model, nouncer, denouncer);
    }

    file.close();
  }
  else {
    std::cerr << "Could not load lyrics file" << std::endl;
  }

  std::cout << "Model ready!" << std::endl;
}

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
void parseLine(std::string in, Model* model, Nouncer* nouncer, Denouncer* denouncer) {
  std::istringstream ss(Utils::flip(in));
  std::string temp;
  std::string pronunciation;
  std::string encoded;

  Word* current = nullptr;
  Word* leader  = nullptr;

  while (ss >> temp) {
    temp = Utils::removePunc(temp);
    temp = Utils::noCaps(temp);

    pronunciation = *(nouncer->lookUp(temp));

    denouncer->addPronunciation(pronunciation, temp);

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
