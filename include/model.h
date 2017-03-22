/*
 * model.h
 *
 * The model used to power the AI's decision making is an adjacency list
 * of all of the provided lyrics.
 *
 * The adjacency list represents an n x n matrix of all the lyrics.
 * The element at the intersection of a word on the x-axis and a word
 * on the y axis represents the number of times the y-axis word preceded
 * the x-axis word in the lyrics.
 */


#ifndef model_H
#define model_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "word.h"
#include "wordList.h"

class Model {
  public:
    Model();
    ~Model();

    // Find the WordList by the given base word
    WordList* find(Word* base);

    // Adds WordList with given Word as base,
    // or if it already exists, increments its frequency
    void addOrUpdate(Word* w);

    // Prints the data structure
    void print(std::string filename);

    // Returns the number of WordLists in the model
    int getSize();

    WordList& operator[](int i);

  private:
    std::vector<WordList>* matrix;
};

#endif
