/*
 * WordList implementation
 */

#include <iostream>
#include <algorithm>
#include "word_list.h"

WordList::WordList(Word w)
{
  baseWord = w;
}

Word& WordList::getBase()
{
  return baseWord;
}

std::vector<Word>& WordList::getFollowers()
{
  return followers;
}

void WordList::addFollower(Word follower)
{
  std::vector<Word>::iterator it;

  //check if 'follower' is already in 'followers[]'
  it = find(followers.begin(), followers.end(), follower);
  //if found

  if (it != followers.end())
  {
    //update 'follower' frequency
    (*it).incrementFrequency();
  }

  else
  {
    //add 'follower' to 'followers[]'
    followers.push_back(follower);
  }
}

std::ostream& operator<<(std::ostream& os, const WordList& wl)
{
  os<<"(base word: "<<wl.baseWord<<")";
  for (int i = 0; i < wl.followers.size(); i++){
    os<<"->("<<wl.followers[i]<<")";
  }
  return os;
}
