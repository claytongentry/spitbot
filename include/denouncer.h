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

#include <string>

#include "nouncer.h"

class Denouncer {
  public:
    Denouncer();
    ~Denouncer();

    std::map<std::string, std::string>* getDict();
    void addPronunciation(std::string pronunciation, std::string word);

  private:
    std::map<std::string, std::string>* dict;
};

#endif // DENOUNCER_H
