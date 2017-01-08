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

#define TEST_FILE "lyrics/test.txt"
#define TRAP_FILE "lyrics/jeezy.txt"

void rap(std::string bar, Model* model, Nouncer* nouncer, Denouncer* denouncer);
void parseFile(std::string filename, Model* model, Nouncer* nouncer, Denouncer* denouncer);
void parseLine(std::string in, Model* model, Nouncer* nouncer, Denouncer* denouncer);

int main(int argc, char *argv[]) {
  std::string file = TRAP_FILE;

  // check for test flag
  if (argc > 1) {
    if (strcmp(argv[1], "-t") == 0) {
      file = TEST_FILE;
    }
    else {
      std::cerr << "bad flag " << std::endl;
      return 0;
    }
  }

  Model* model         = new Model();
  Nouncer* nouncer     = new Nouncer();
  Denouncer* denouncer = new Denouncer();

  parseFile(file, model, nouncer, denouncer);

  std::string bar;
  std::cout << "Gimme a bar" << std::endl;
  std::getline(std::cin, bar);

  rap(bar, model, nouncer, denouncer);

  delete model;
  delete nouncer;
  delete denouncer;
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

    delete battle;
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

  //add place holder: every word will be a "leader" of _NULL_
  Word* _NULL_ = new Word("_NULL_", "");
  model->addOrUpdate(_NULL_);
  delete _NULL_;

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
  std::string nounce;
  std::string encoded;
  std::string stressPattern;

  Word current;
  Word leader;

  Word* _NULL_ = new Word("_NULL_", "");

  while (ss >> temp) {
    //preprocess temp
    temp = Utils::removePunc(temp);
    temp = Utils::noCaps(temp);

    //get pronunciation
    nounce = nouncer->getNounce(temp);

    //add pronunciation:word pair to denouncer
    denouncer->addNounce(nounce, temp);

    // Determine word's stress pattern
    stressPattern = nouncer->doStressPattern(temp);

    //pick off the word
    current = Word(temp, stressPattern);

    //add word to _NULL_
    WordList* list_ptr = model -> find(_NULL_);
    (*list_ptr).addLeader(current);

    //add current to the model
    model->addOrUpdate(&current);

    // if first word on (reversed) line => last word on a line => current not a leader
    if (leader.getName()== "") {
      leader = current;
    }

    //other wise add current to leader's list
    else {
      list_ptr = model -> find(&leader);

      //if leader is not in the model
      if (list_ptr != nullptr) {
        (*list_ptr).addLeader(current);
        leader = current;
      }
      else {
        std::cerr << "Could not get leader." << std::endl;
      }
    }
  }

  delete _NULL_;
}
