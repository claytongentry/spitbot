/*
 * word.cpp
 */

#include "word.h"

Word::Word(){
  value = "";
  frequency = 0;
}

Word::Word(std::string val)
{
  std::string text;
  std::remove_copy_if(val.begin(), val.end(), std::back_inserter(text),std::ptr_fun<int,int>(&std::ispunct));

  value = val;
  frequency = 1;
}

Word::~Word()
{

}

Word::Word(const Word& w)
{
  value = w.value;
  frequency = w.frequency;
}

std::string Word::getVal()
{
  return value;
}

int Word::getFrequency()
{
  return frequency;
}

void Word::setVal(std::string newValue)
{
  value = newValue;
}

void Word::setFrequency(int newFrequency)
{
  frequency = newFrequency;
}

void Word::incrementFrequency()
{
  frequency++;
}

bool Word::operator==(const Word& w)
{
  return (w.value == this->value);
}

std::ostream& operator<<(std::ostream& os, const Word& w)
{
  os<<w.value<<" | "<<w.frequency;
  return os;
}
