/*
 * Battle implementation
 */

#include "battle.h"

Battle::Battle(std::string given, Model* m, Nouncer* nouncer, Denouncer* denouncer) {
  findLastAndCount(given);

  std::string lastWord = getLast();
  int numWords         = getNumWords();
  Rhymer* rhymer       = new Rhymer(nouncer, denouncer);

  Word* rhyme = rhymer->rhyme(lastWord);

  delete rhymer;

  fire = traceBack(rhyme, numWords, m);

  delete rhymer;
}

void Battle::spit() {
  std::cout << fire << std::endl;
}

Battle::~Battle() {

}

std::string Battle::traceBack(Word* base, int numWords, Model* m) {
  Word* _NULL_ = new Word("_NULL_");
  std::string response = base->getVal();

  //construct response by traversing the adjacency-list
  for (int addedWords = 1; addedWords < numWords; addedWords++) {

    // find word in model
    WordList* leadersList = m->find(base);

    Word* leader = leadersList->pickLeader();

    //if _NULL_
    if (leader->getVal() == "_NULL_") {

      leadersList = m->find(_NULL_);
      leader = leadersList->pickLeader();

    }

    // add it to the response
    response = leader->getVal() + " " + response;
    std::cout<<response<<std::endl;
    // set leader as new base
    base = leader;
  }
  delete _NULL_;

  return response;
}

void Battle::findLastAndCount(std::string given) {
  std::istringstream ss(given);
  std::string last;

  int count = 0;
  while (ss >> last) {
    count++;
  }

  inLast   = last;
  numWords = count;
}

std::string Battle::getLast() {
  return inLast;
}

int Battle::getNumWords() {
  return numWords;
}
