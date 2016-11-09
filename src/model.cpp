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
    {
      std::istringstream ss(line);
      std::string temp;

      Word* current = nullptr;
      Word* previous = nullptr;

      while(ss>>temp){
        std::string result;
        std::remove_copy_if(temp.begin(), temp.end(), std::back_inserter(result),std::ptr_fun<int,int>(&std::ispunct));
        //word to insert into matrix
        current = new Word(result);
        //std::cout<<"current word: "<<*current<<std::endl;
        //if first word on line
        if(previous == nullptr){
          //std::cout<<"no previous word"<<std::endl;
          addToMatrix(*current);
          previous = current;

        }

        //if not first word on line
        else{
          addToMatrix(*current);
          //std::cout<<"previous word: "<<*previous<<std::endl;
          //find previous in matrix
          std::vector<WordList>::iterator it;
          for(it = matrix.begin(); it != matrix.end(); ++it){
            if ((*it).getBase() == *previous){break;}
          }
          //if found
          if(it != matrix.end()){
            (*it).addFollower(*current);
            previous = current;
          }
          //if for some reason the previous isn't in there...
          else{
            std::cout<<"SOMETHING IS WRONG"<<std::endl;
          }
        }
      }
    }
    file.close();
  }
  else
    std::cout << "Could not load lyrics file.\n";
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
  if(it == matrix.end()){
    //std::cout<<"added to matrix"<<std::endl;
    //create a new word_list & add it to matrix
    WordList wl(w);
    matrix.push_back(wl);
  }
  //if found
  else{
    //increase its frequency
    (*it).getBase().incrementFrequency();
  }
}
/*not right please change*/
void Model::print(){
  for (int i = 0; i < matrix.size(); i++){
    std::cout<<i+1<<": "<<matrix[i]<<std::endl;
  }
}
