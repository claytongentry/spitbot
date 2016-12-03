/*
 * Model implementation
 */

#include "model.h"

/*
 * Constructs a new Model object using a text file
 * of lyrics. Models are adjacency list data structures
 * that map the frequency with which Words precede other Words
 */
Model::Model() {
  matrix = new std::vector<WordList>;
}

/*
 * Returns a pointer to the WordList
 * where <leader> is the base word.
 *
 * If <leader> is not found, returns a nullptr.
 */
WordList* Model::find(Word* leader) {
  std::vector<WordList>::iterator it;

  for(it = matrix->begin(); it != matrix->end(); ++it)
    if ((*it).get_base() == *leader)
      return &(*it);

  return nullptr;
}

/*
 * If Word already exists as base word in Model,
 * increments its frequency.
 *
 * Otherwise, increments its frequency.
 */
void Model::addOrUpdate(Word* w) {
  WordList* list_ptr = find(w);

  if (list_ptr == nullptr) {
    WordList wl(*w);
    matrix->push_back(wl);
  }

  else
    (*list_ptr).get_base().incrementFrequency();
}

/*
 * Prints the model
 */
void Model::print(std::string filename) {
  std::ofstream f(filename);
  for (int i = 0; i < matrix->size(); i++) {
    f << i+1 << ": " << matrix->at(i) << std::endl;
  }
}

int Model::getSize() {
  return matrix->size();
}

WordList& Model::operator[](int i) {
  return (matrix->at(i));
}
