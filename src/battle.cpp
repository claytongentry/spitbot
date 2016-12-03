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

  fire = traceBack(rhyme, numWords, m);
}

void Battle::spit() {
  std::cout << fire << std::endl;
}

std::string Battle::traceBack(Word* base, int numWords, Model* m) {
  std::string response = base->getVal();

  //construct response by traversing the adjacency-list
  for (int addedWords = 1; addedWords < numWords; addedWords++) {

    // find word in model
    WordList* leadersList = m->find(base);

    // if no leaders return "DEAD END"
    if (leadersList->getSize() == 0) {
      std::cout<<"DEAD END"<<std::endl;
      return response;
    }

    Word* leader = leadersList->pickLeader();

    // add it to the response
    response = leader->getVal() + " " + response;

    // set leader as new base
    base = leader;
  }

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
