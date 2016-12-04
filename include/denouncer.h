/*
 * denouncer.h
 *
 * A class for building a reverse pronunciation dictionary.
 *
 * This class maps encoded pronunciations to their respective words and enables
 * functionality to optimize finding rhyming words.
 */

#ifndef DENOUNCER_H
#define DENOUNCER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Denouncer {
  public:
    Denouncer();
    ~Denouncer();

    std::vector<std::pair<std::string, std::string>>* getDict();

    // Add a nounce and corresponding word to the vector
    void addNounce(std::string nounce, std::string word);

    // Get the index in the sorted vector for the given nounce
    int getIndex(std::string nounce);

    // Look up the value at the given index in the vector
    std::string lookUp(int index);

    // Look up the value of the given nounce in the vector
    std::string lookUp(std::string nounce);

    // Prints the data structure
    void print(std::string filename);

    // size of dict
    int getSize() {return dict->size();}

  private:
    std::vector<std::pair<std::string, std::string>>* dict;

    int binarySearch(std::string nounce, int start, int end);

    bool find(std::pair<std::string, std::string>);
};

#endif // DENOUNCER_H
