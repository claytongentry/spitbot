/*
 * Model implementation
 */

#include "model.h"

/*
 * Constructs a new Model object using a text file
 * of lyrics. Models are adjacency list data structures
 * that map the frequency with which Words precede other Words
 */
Model::Model(std::string lyrics_file) {
  std::string line;
  std::ifstream file(lyrics_file);

  if (file)
  {
    while(getline(file, line))
      parse_line(line);

    file.close();
  }

  else
    std::cerr << "Could not load lyrics file" << std::endl;
}

/*
 * Parses a line
 *
 * Each new unique word is appended to the adjacency list
 * as a base word, and its preceding word is instantiated
 * as a node in its leaders vector. If the leader has already
 * been instantiated, its frequency is updated.
 *
 * Lines are processed individually to ensure the model
 * doesn't assume false positive adjacency between the
 * last word of a preceding line and the first word of
 * its successor.
 */
void Model::parseLine(std::string in) {
  std::istringstream ss(flip(in));
  std::string temp;
  std::string pronunciation;

  Word* current = nullptr;
  Word* leader  = nullptr;

  // TODO: Make this not spaghetti.
  while (ss >> temp) {
    pronunciation = Nouncer::lookup(temp);
    Denouncer::addWord(temp, pronunciation)

    current = new Word(temp);
    add_or_update(current);

    // if first word on (reversed) line
    if (leader == nullptr) {
      leader = current;
    }
    else {
      WordList* list_ptr = find(leader);

      if (list_ptr != nullptr) {
        (*list_ptr).add_leader(*current);
        leader = current;
      }
      else {
        std::cerr << "Could not get leader." << std::endl;
      }
    }
  }
}

/*
 * Returns a pointer to the WordList
 * where <leader> is the base word.
 *
 * If <leader> is not found, returns a nullptr.
 */
WordList* Model::find(Word* leader)
{
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
void Model::add_or_update(Word* w)
{
  WordList* list_ptr = find(w);

  if (list_ptr == nullptr) {
    WordList wl(*w);
    matrix.push_back(wl);
  }

  else
    (*list_ptr).get_base().incrementFrequency();
}

/*
 * Reverses a string while preserving individual words
 */
std::string Model::flip(std::string text)
{
  std::string out;
  std::istringstream buffer(text);

  for ( auto i  = std::istream_iterator<std::string>(buffer);
             i != std::istream_iterator<std::string>();
             ++i )
    out = *i + ' ' + out;

  return out;
}

/*
 * Prints the model
 */
void Model::print()
{
  for (int i = 0; i < matrix.size(); i++)
    std::cout<<i+1<<": "<<matrix[i]<<std::endl;
}

int Model::getSize(){
  return matrix.size();
}

WordList& Model::operator[](int i){
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
