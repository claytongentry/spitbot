/*functionality of the rap bot
 *A battle object will take in a line provided by the user
*1st iteration will simply choose a random word in the
*adjacency-list and return a line of equal number of words
*/

#ifndef BATTLE_H
#define BATTLE_H

#include "model.h"

class Battle {
public:
  Battle();

  //returns a line given the input string
  std::string traceBack();

  //returns the last word in the input string
  std::string getLast();

  //return the number of words in the input string
  int getNumWords();

private:
  //given input line
  std::string given;

  Model* m;
  std::string inLast;
  int numWords;

  //used in constructor
  void findLastAndCount();


};
#endif //BATTLE_H
