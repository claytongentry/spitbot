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
  std::vector<Word>::iterator it;
  std::string line;
  std::ifstream file(lyrics_file);

  if(file.is_open())
  {
    while(getline(file, line))
      parse_line(line);

    file.close();
  }
  else
    std::cerr << "Could not load lyrics file.\n";
}

void Model::parse_line(std::string line)
{
  std::istringstream ss(line);
  std::string temp;

  Word* current = nullptr;
  Word* leader  = nullptr;

  while(ss>>temp){
    current = new Word(temp);
    addToMatrix(*current);

    //if first word on line
    if(leader == nullptr)
      leader = current;

    //if not first word on line
    else {
      //find leader in matrix
      std::vector<WordList>::iterator it;
      for(it = matrix.begin(); it != matrix.end(); ++it){
        if ((*it).getBase() == *leader) break;
      }

      //if found
      if(it != matrix.end()){
        (*it).addFollower(*current);
        leader = current;
      }

      //if for some reason the leader isn't in there...
      else{
        std::cerr<<"Could not get leader."<<std::endl;
      }
    }
  }
}

int Model::getSize(){
  return matrix.size();
}

void Model::addToMatrix(Word w){
  //find it in the matrix
  std::vector<WordList>::iterator it;
  for(it = matrix.begin(); it != matrix.end(); ++it){
    if ((*it).getBase() == w){break;}
  }

  //if not found
  if(it == matrix.end())
    add_word_list(w);
  else
    (*it).getBase().incrementFrequency();
}

// Create a new word_list & add it to matrix
void Model::add_word_list(Word w) {
  WordList wl(w);
  matrix.push_back(wl);
}

/*not right please change*/
void Model::print(){
  for (int i = 0; i < matrix.size(); i++){
    std::cout<<i+1<<": "<<matrix[i]<<std::endl;
  }
}
