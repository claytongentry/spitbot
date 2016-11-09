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

#include "model.h"
#include "word.h"
#include "word_list.h"

#define LYRICS_FILE "lyrics/lyrics.txt"
#define TEST_FILE "lyrics/test.txt"

int main(int argc, char *argv[])
{
  std::string bar;
  std::cout << "Gimme a bar\n";
  std::getline(std::cin, bar);

  Model *m = new Model(TEST_FILE);

  std::cout<<m->getSize()<<std::endl;
  m->print();

  return 0;
  /*
  Word myword("jeezy");
  Word another("likes");
  WordList wl(myword);
  std::cout<<wl.getBase()<<std::endl;
  wl.addFollower(another);
  std::cout<<wl.getFollowers().size()<<std::endl;
//something weird here
  std::cout<<wl.getFollowers()[0]<<std::endl;
  wl.addFollower(another);
  std::cout<<wl.getFollowers().size()<<std::endl;
  //something weird here
  std::cout<<wl.getFollowers()[0]<<std::endl;
  */
}
