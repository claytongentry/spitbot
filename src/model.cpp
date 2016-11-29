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
  matrix = new std::vector<WordList>()
}

/*
 * Returns a pointer to the WordList
 * where <leader> is the base word.
 *
 * If <leader> is not found, returns a nullptr.
 */
WordList* Model::find(Word* leader) {
  std::vector<WordList>::iterator it;

  for(it = matrix.begin(); it != matrix.end(); ++it)
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
    matrix.push_back(wl);
  }

  else
    (*list_ptr).get_base().incrementFrequency();
}

/*
 * Prints the model
 */
void Model::print() {
  for (int i = 0; i < matrix.size(); i++) {
    std::cout << i+1 << ": " << matrix[i] << std::endl;
  }
}

int Model::getSize() {
  return matrix.size();
}

WordList& Model::operator[](int i) {
  return matrix[i];
}

void Model::visualize(std::string outFile) {

  std::ofstream file(outFile);
  if (file) {
    //print first line which is the words
    std::string row = ",";
    std::vector<Word> corpus;
    for (int i = 0; i < matrix.size(); i++) {
      row = row + matrix[i].get_base().getVal() + ",";
      corpus.push_back(matrix[i].get_base());
    }
    row = row + "\n";
    file << row;
    //print the other rows "word, freq, freq, ..."
    for (int i = 0; i < matrix.size(); i++) {
      row = matrix[i].get_base().getVal() + ",";

      //for each word in corpus put the freq. found in the wordList
      for (int j = 0; j < corpus.size(); j++) {
        Word col = corpus[j];
        std::vector<Word>::iterator it;
        it = std::find(matrix[i].get_leaders().begin(), matrix[i].get_leaders().end(), col);
        //if not found freq = 0;
        if (it == matrix[i].get_leaders().end()) {
          row = row + "0,";
        }
        else {
          std::string f = std::to_string((*it).getFrequency());
          row = row + f + ",";
        }
      }

      row = row + "\n";
      file << row;
    }
    file.close();
  }
}
