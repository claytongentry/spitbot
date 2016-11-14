#include "battle.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

Battle::Battle() {
  m = new Model("./lyrics/lyrics.txt");

  std::cout<<"gimme a bar\n";
  std::getline(std::cin, given);
  findLastAndCount();
}

std::string Battle::traceBack() {
  //find a word that rhymes with the "last" in Model
  //outLastfindRhyme(last)

  std::string response;

  //intialize random
  std::srand(std::time(NULL));

  /*this step will be replace by rhyming*/
  //random word from from model
  int baseIndex = rand() % m->getSize();
  Word base = (*m)[baseIndex].get_base();
  /*this step will be replace by rhyming*/

  //add base to repsonse
  response = base.getVal() + " " + response;

  //construct response by traversing the adjacency-list
  for (int addedWords = 1; addedWords < numWords; addedWords++) {
    //find word in model
    WordList* leadersList = m->find(&base);

    //find a random word in base's the leader list
    int numLeaders = leadersList->getSize();
    //if no leaders return "DEAD END"
    if(numLeaders == 0) {
      std::cout<<"DEAD END"<<std::endl;
      return response;
    }
    /*if a word doesn't have any leaders we need to do something that...*/
    int leaderIndex = rand() % numLeaders;
    Word leader = leadersList->get_leaders()[leaderIndex];

    //add it to the response
    response = leader.getVal() + " " + response;

    //set leader as new base
    base = leader;
  }
  return response;
}

void Battle::findLastAndCount() {
  std::istringstream ss(given);
  std::string last;
  int count = 0;
  while(ss>>last) {
    count++;
  }

  inLast = last;
  numWords = count;
}

std::string Battle::getLast() {
  return inLast;
}

int Battle::getNumWords() {
  return numWords;
}
