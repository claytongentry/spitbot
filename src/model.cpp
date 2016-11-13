/*
 * Model implementation
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "model.h"

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

void Model::parse_line(std::string line)
{
  std::istringstream ss(line);
  std::string temp;

  Word* current = nullptr;
  Word* leader  = nullptr;

  while (ss>>temp)
  {
    current = new Word(temp);
    addToMatrix(current);

    //if first word on line
    if(leader == nullptr)
      leader = current;

    //if not first word on line
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

WordList* Model::find(Word* leader)
{
  std::vector<WordList>::iterator it;

  for(it = matrix.begin(); it != matrix.end(); ++it)
    if ((*it).getBase() == *leader)
      return &(*it);

  return nullptr;
}

void Model::addToMatrix(Word* w)
{
  WordList* list_ptr = find(w);

  if (list_ptr == nullptr)
    add_word_list(w);

  else
    (*list_ptr).getBase().incrementFrequency();
}

// Create a new word_list & add it to matrix
void Model::add_word_list(Word* w)
{
  WordList wl(*w);
  matrix.push_back(wl);
}

void Model::print()
{
  for (int i = 0; i < matrix.size(); i++){
    std::cout<<i+1<<": "<<matrix[i]<<std::endl;
  }
}
