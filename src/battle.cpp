/*
 * Battle implementation
 */ 

#include "battle.h"

Battle::Battle(std::string given, Model* m, Nouncer* pd) {
  findLastAndCount(given);

  std::string lastWord = getLast();
  int numWords         = getNumWords();
  Rhymer* rhymer       = new Rhymer(pd);

  Word* rhyme = rhymer->rhyme(lastWord, m);

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

    // find a random word in base's the leader list
    int numLeaders = leadersList->getSize();

    // if no leaders return "DEAD END"
    if (numLeaders == 0) {
      std::cout<<"DEAD END"<<std::endl;
      return response;
    }

    // TODO: Use frequency as weight
    int leaderIndex = rand() % numLeaders;
    Word leader     = leadersList->get_leaders()[leaderIndex];

    // add it to the response
    response = leader.getVal() + " " + response;

    // set leader as new base
    base = &leader;
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
