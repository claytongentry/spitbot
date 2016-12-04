/*
 * wordList.h
 *
 * A WordList is a key-value data structure, where the key is a base word
 * and the value is a vector of tuples. Each tuple in the vector includes
 * a word that precedes the base word in Jeezy's lyrics and the frequency
 * with which does so.
 *
 */

#ifndef wordList_H
#define wordList_H

#include <cstdlib>
#include <ctime>
#include <vector>

#include "word.h"

class WordList {
  public:
    WordList(Word base_word);
    ~WordList();

    // Get the base word
    Word& get_base();

    // Get the leaders list
    std::vector<Word>& get_leaders();

    // Add a leader to the leaders list for the given leader
    void add_leader(Word leader);

    // Select a leader from the leaders list
    Word* pickLeader();

    // Get the size of the leaders list
    int getSize();

    friend std::ostream& operator<<(std::ostream& os, const WordList& wl);

  private:
    Word base_word;
    std::vector<Word> leaders;
};

#endif
