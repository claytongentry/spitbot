/*
 * word_list.h
 *
 * A WordList is a map data structure, where the key is a base word
 * and the value is a vector of tuples. Each tuple includes a word
 * that succeeds the base word in Jeezy's lyrics and the frequency
 * with which does so.
 *
 */

#ifndef word_list_H
#define word_list_H

using namespace std;

class WordList
{

  public:
    update_frequency(string base);
    append_successor(string base);

};

#endif
