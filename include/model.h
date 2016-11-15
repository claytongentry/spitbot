/*
 * model.h
 *
 * The model used to power the AI's decision making is an adjacency list
 * of all of Young Jeezy's lyrics.
 *
 * The adjacency list represents an n x n matrix of all the lyrics.
 * The element at the intersection of a word on the x-axis and a word
 * on the y axis represents the number of times the y-axis word preceded
 * the x-axis word in Jeezy's songs.
 */


#ifndef model_H
#define model_H

#include <vector>
#include "word.h"
#include "word_list.h"

class Model {
  public:
    Model(std::string filename);

    WordList* find(Word* leader);

    Word* init_word(std::string val);

    void parse_line(std::string line);
    void add_or_update(Word* w);
    void print();

    void visualize(std::string outFile);

    int getSize();

    WordList& operator[](int i);

  private:
    std::vector<WordList> matrix;
    std::string flip(std::string text);

};

#endif
