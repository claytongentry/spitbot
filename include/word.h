/*
 * word.h
 * word will hold data about lyrics in jeezy db
 * for now its only used in the adjacency matrix
 */

#ifndef WORD_H
#define WORD_H

#include <string>
#include <iostream>

class Word{
private:
  //string of the word itself
  std::string value;

  //number of times it occurs in the matrix
  //i.e. # of times it follows the word whose list its in
  int frequency;

public:
  Word(std::string val);
  ~Word();

  Word(const Word& w);

  std::string getVal();
  void setVal(std::string newWord);

  int getFrequency();
  void setFrequency(int newFrequency);
  void incrementFrequency();

  bool operator==(const Word& w);

  friend std::ostream& operator<<(std::ostream& os, const Word& w){
    os<<w.value<<", "<<w.frequency;
    return os;
  }



};
#endif //WORD_H
