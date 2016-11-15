#include <cstdlib>
#include <ctime>
#include <sstream>

#include "battle.h"

Battle::Battle(std::string given) {
  findLastAndCount(given);
}

std::string Battle::spit() {
  std::cout << fire << std::endl;
}

std::string Battle::traceBack() {
  std::string response;

  //intialize random
  std::srand(std::time(NULL));

  /* TODO: Replace this with rhyme selection */
  int baseIndex = rand() % m->getSize();
  Word base = (*m)[baseIndex].get_base();

  //add base to response
  response = base.getVal() + " " + response;

  //construct response by traversing the adjacency-list
  for (int addedWords = 1; addedWords < numWords; addedWords++) {

    //find word in model
    WordList* leadersList = m->find(&base);

    //find a random word in base's the leader list
    int numLeaders = leadersList->getSize();

    //if no leaders return "DEAD END"
    if (numLeaders == 0) {
      std::cout<<"DEAD END"<<std::endl;
      return response;
    }

    /*if a word doesn't have any leaders we need to do something that...*/
    int leaderIndex = rand() % numLeaders;
    Word leader     = leadersList->get_leaders()[leaderIndex];

    //add it to the response
    response = leader.getVal() + " " + response;

    //set leader as new base
    base = leader;
  }

  return response;
}

void Battle::findLastAndCount(std::string given) {
  std::istringstream ss(given);
  std::string last;

  int count = 0;
  while (ss>>last) {
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
