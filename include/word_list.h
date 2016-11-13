/*
 * word_list.h
 *
 * A WordList is a map data structure, where the key is a base word
 * and the value is a vector of tuples. Each tuple includes a word
 * that succeeds the base word in Jeezy's lyrics and the frequency
 * with which does so.
 *
 *edit:
 *not really a map (though we could make it so)
 *<Word, vector<Word>
 *
 */

#ifndef word_list_H
#define word_list_H

#include "Word.h"
#include <vector>

class WordList
{
  public:
    WordList(Word baseWord);

    Word& getBase();

    std::vector<Word>& getFollowers();

    void addFollower(Word follower);

    friend std::ostream& operator<<(std::ostream& os, const WordList& wl);

  private:
    Word baseWord;
    std::vector<Word> followers;
};

#endif
