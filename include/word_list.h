/*
 * word_list.h
 *
 * A WordList is a key-value data structure, where the key is a base word
 * and the value is a vector of tuples. Each tuple in the vector includes
 * a word that precedes the base word in Jeezy's lyrics and the frequency
 * with which does so.
 *
 */

#ifndef word_list_H
#define word_list_H

#include <vector>

#include "word.h"

class WordList
{
  public:
    WordList(Word base_word);

    Word& get_base();

    std::vector<Word>& get_leaders();

    void add_leader(Word leader);

    int getSize();

    friend std::ostream& operator<<(std::ostream& os, const WordList& wl);

  private:
    Word base_word;
    std::vector<Word> leaders;
};

#endif
