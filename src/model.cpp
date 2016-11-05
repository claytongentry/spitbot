/*
 * Model implementation
 */

#include <iostream>
#include <fstream>
#include <string>

#include "model.h"

Model::Model(string lyrics_file)
{
  std::string line;
  std::ifstream file(lyrics_file);
  if(file.is_open())
  {
    while(getline(file, line))
    {
      std::cout << line << '\n';
    }
    file.close();
  }
  else
    std::cout << "Could not load lyrics file.\n";
}
