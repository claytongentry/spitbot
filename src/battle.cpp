/*
 * Battle implementation
 */

#include "battle.h"

Battle::Battle(std::string given, Model* m, Nouncer* nouncer, Denouncer* denouncer) {
  findLastAndCount(given, nouncer);

  std::string lastWord = getLast();
  int numWords         = getNumWords();
  Rhymer* rhymer       = new Rhymer(nouncer, denouncer);
  Word* rhyme          = new Word(rhymer->rhyme(lastWord));

  fire = traceBack(rhyme, numWords, m);

  delete rhymer;
  delete rhyme;
}

void Battle::spit() {
  std::cout << fire << std::endl;
}

Battle::~Battle(){}

std::string Battle::traceBack(Word* base, int numWords, Model* m) {
  Word* _NULL_         = new Word("_NULL_");
  std::string response = base->getVal();

  //construct response by traversing the adjacency-list
  for (int addedWords = 1; addedWords < numWords; addedWords++) {

    // find word in model
    WordList* leadersList = m->find(base);
    Word* leader          = leadersList->pickLeader();

    // if _NULL_
    if (leader->getVal() == "_NULL_") {
      leadersList = m->find(_NULL_);
      leader      = leadersList->pickLeader();
    }

    // add it to the response
    response = leader->getVal() + " " + response;

    // set leader as new base
    base = leader;
  }

  delete _NULL_;

  return response;
}

void Battle::findLastAndCount(std::string given, Nouncer* nouncer) {
  std::istringstream ss(given);
  std::string last;

  std::string* nounce;

  int words = 0;
  int syls = 0;

  while (ss >> last) {
    words++;

    //get nounce from word
    nounce = nouncer->lookUp(last);
    syls += Nouncer::getSylCount(*nounce);

  }

  inLast   = last;
  numWords = words;
  numSyls = syls;
  std::cout<<"Number of syls in given line: "<<numSyls<<std::endl;
}

std::string Battle::getLast() {
  return inLast;
}

int Battle::getNumWords() {
  return numWords;
}
