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
      while(ss>>temp){
        it = find(words.begin(), words.end(), temp);
        if (it == words.end()){
          Word x(temp);
          words.push_back(x);
        }
        else{
          it->incrementFrequency();
        }
      }
    }
    file.close();
  }
  else
    std::cout << "Could not load lyrics file.\n";
}

int Model::getSize(){
  return words.size();
}

void Model::print(){
  for (int i = 0; i < words.size(); i++){
    std::cout<<words[i]<<std::endl;
  }
}
