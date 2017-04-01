/*
 * WordList implementation
 */

#include "wordList.h"

Word WordList::_NULL_("_NULL_", "");

/*
 * Instantiates a new WordList with given base_word
 * _NULL_ is a place holder that will indicate to find a
 * non-leader in Battle::traceBack()
 */
WordList::WordList(Word w) {
  base_word = w;
  if(w.getVal() != "_NULL_") addLeader(_NULL_);
}

WordList::~WordList(){};

/*
 * Returns base word
 */
Word& WordList::getBase() {
  return base_word;
}

/*
 * Returns leaders
 */
std::vector<Word>& WordList::getLeaders() {
  return leaders;
}

/*
 * Checks if 'leader' is already in 'leaders[]'
 * Otherwise adds leader to leaders[]
 */
void WordList::addLeader(Word leader) {

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
Word* WordList::pickLeader() {
  srand(time(NULL));
  Word* leader = nullptr;
  int count    = leaders.size();
  int max      = 0;
  int score;

  for (int i = 0; i < count; i++) {

    int r = rand() % 10;
    score = leaders[i].getFrequency() * r;

    if (score >= max) {
      max    = score;
      leader = &leaders[i];
    }
  }

  return leader;
}

int WordList::getSize() {
  return leaders.size();
}
