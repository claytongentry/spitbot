/*
 * Model implementation
 */

#include "model.h"

/*
 * Constructs a new Model object using a text file
 * of lyrics. Models are adjacency list data structures
 * that map the frequency with which Words precede other Words
 */
Model::Model() : Matrix() {}

Model::~Model() {}

/*
 * Returns a pointer to the WordList
 * where <leader> is the base word.
 *
 * If <leader> is not found, returns a nullptr.
 */
WordList* Model::find(Word leader) {
  WordList wl(leader);

  int index = Matrix::findRow(wl);

  if (index == Matrix::getSize())
    return nullptr;
  else
    return &(rows[index]);

}

/*
 * If Word already exists as base word in Model,
 * increments its frequency.
 *
 * Otherwise, instantiates a new WordList with
 * the Word as its base and appends to the model.
 */
void Model::addOrUpdate(Word word) {
  WordList* list_ptr = find(word);

  if (list_ptr == nullptr)
    addRow(WordList(word));

  else
    (*list_ptr).getBase().incrementFrequency();

}
