/*
 * word.h
 *
 * A Word will hold data about lyrics in jeezy db
 * for now its only used in the adjacency matrix
 */

#ifndef WORD_H
#define WORD_H

#include <algorithm>
#include <iostream>
#include <locale>
#include <string>

#include "utils.h"

class Word {
  public:
    Word();
    Word(std::string val);
    ~Word();

    Word(const Word& w);

    // Get the string value of the Word
    std::string getVal();

    // Set the string value of the Word
    void setVal(std::string newWord);

    // If a leader, get the number of times the word leads its base word
    // If a base word, get the number of times it appears in the model
    int getFrequency();

    // Set the Word's frequency
    void setFrequency(int newFrequency);

    // Increment the frequency count by 1
    void incrementFrequency();

    bool operator==(const Word& w);

    friend std::ostream& operator<<(std::ostream& os, const Word& w);

  private:

    // String of the word itself
    std::string value;

    // Number of times it occurs in the matrix
    // i.e. # of times it follows the word whose list its in
    int frequency;
};

#endif //WORD_H
