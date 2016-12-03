/*
 * WordList implementation
 */

#include "wordList.h"

/*
 * Instantiates a new WordList with given base_word
 */
WordList::WordList(Word w) {
  base_word = w;
}

/*
 * Returns base word
 */
Word& WordList::get_base() {
  return base_word;
}

/*
 * Returns leaders
 */
std::vector<Word>& WordList::get_leaders() {
  return leaders;
}

/*
 * Checks if 'leader' is already in 'leaders[]'
 * Otherwise adds leader to leaders[]
 */
void WordList::add_leader(Word leader) {
  std::vector<Word>::iterator it;

  it = find(leaders.begin(), leaders.end(), leader);

  if (it != leaders.end())
    (*it).incrementFrequency();

  else
    leaders.push_back(leader);
}

/*
 * Select a leader from the list
 */
Word& WordList::pickLeader() {
  int count    = leaders.size();
  float max    = 0;
  Word* leader = nullptr;

  for (int i = 0; i < count; i++) {
    float score = leaders[i].getFrequency() * (rand() % 10);

    if (score > max) {
      max    = score;
      leader = &leaders[i];
    }
  }

  return *leader;
}

int WordList::getSize() {
  return leaders.size();
}

std::ostream& operator<<(std::ostream& os, const WordList& wl) {
  os<<"(base word: "<<wl.base_word<<")";

  for (int i = 0; i < wl.leaders.size(); i++)
    os<<"->("<<wl.leaders[i]<<")";

  return os;
}
