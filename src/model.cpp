/*
 * Model implementation
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "model.h"

/*
 * Constructs a new Model object using a text file
 * of lyrics. Models are adjacency list data structures
 * that map the frequency with which Words precede other Words
 */
Model::Model(std::string lyrics_file)
{
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
 * Because our model depends on reversed line
 */
void Model::parse_line(std::string in)
{
  std::string line = flip(in);

  std::istringstream ss(line);
  std::string temp;

  Word* current = nullptr;
  Word* leader  = nullptr;

  while (ss >> temp)
  {
    current = new Word(temp);
    add_or_update(current);

    // if first word on (reversed) line
    if (leader == nullptr)
      leader = current;

    else
    {
      WordList* list_ptr = find(leader);

      if (list_ptr != nullptr)
      {
        (*list_ptr).addFollower(*current);
        leader = current;
      }

      else
        std::cerr<<"Could not get leader."<<std::endl;
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
    if ((*it).getBase() == *leader)
      return &(*it);

  return nullptr;
}

/*
 * If Word already exists as base word in Model,
 * increments its frequency.
 *
 * Otherwise
 */
void Model::add_or_update(Word* w)
{
  WordList* list_ptr = find(w);

  if (list_ptr == nullptr) {
    WordList wl(*w);
    matrix.push_back(wl);
  }

  else
    (*list_ptr).getBase().incrementFrequency();
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
