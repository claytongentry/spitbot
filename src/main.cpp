/*
 * JeezyAI is a rap bot that emulates Young Jeezy.
 *
 * Given a bar, JeezyAI will return a rhyme on beat. The AI is trained on a
 * bank of Jeezy lyrics, so it spits like Jeezy.
 *
 * Cameron Matson, Clayton Gentry
 */

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  std::string bar;

  std::cout << "Gimme a bar\n";
  std::getline(std::cin, bar);

  return 0;
}
