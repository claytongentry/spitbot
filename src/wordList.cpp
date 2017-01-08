/*
 * WordList implementation
 */

#include "wordList.h"

Word WordList::_NULL_("_NULL_", "");

WordList::WordList() : Row() {

}

/*
 * Instantiates a new WordList with given base_word
 * _NULL_ is a place holder that will indicate to find a
 * non-leader in Battle::traceBack()
 */
WordList::WordList(Word word) : Row(word){
  if(word.getName() != "_NULL_") addLeader(_NULL_);
}

WordList::~WordList(){};

/*
 * Returns base word
 */
Word WordList::getBase() {
  return primary;
}

/*
 * Returns leaders
 */
std::vector<Word>& WordList::getLeaders() {
  return columns;
}

/*
 * Checks if 'leader' is already in 'columns[]'
 * Otherwise adds leader to columns[]
 */
void WordList::addLeader(Word leader) {

  int index = addElement(leader);
  if (index == -1)
    primary.incrementFrequency();
  else
    columns[index].incrementFrequency();
}

/*
 * Select a leader from the list
 */
Word WordList::pickLeader() {
  srand(time(NULL));
  Word leader;
  int count    = columns.size();
  int max      = 0;
  int score;

  for (int i = 0; i < count; i++) {

    int r = rand() % 10;
    score = columns[i].getFrequency() * r;

    if (score >= max) {
      max    = score;
      leader = columns[i];
    }
  }

  return leader;
}

int WordList::getSize() {
  return columns.size();
}
