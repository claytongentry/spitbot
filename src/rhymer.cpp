/*
 * Rhymer implementation
 */

#include <iostream>
#include <string>

#include "rhymer.h"
#include "model.h"

Rhymer::Rhymer(Nouncer* n) {
  this->n = n;
}

Word* Rhymer::rhyme(std::string base_word, Model* m) {
  std::string* base_nounce = n->lookUp(base_word);
  std::cout << "Encoded phoneme for base " << base_word << ": " << *base_nounce << std::endl;

  /*TODO:lookup a word that rhymes with base_nounce by going
   * a random(?) distance away from base_nounce in decnouncer
   */



  Word* word = new Word("gravy");
  return word;
}
