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

/*
 * Checks if 'follower' is already in 'followers[]'
 * Otherwise adds follower to followers[]
 */
void WordList::addFollower(Word follower)
{
  std::vector<Word>::iterator it;

  it = find(followers.begin(), followers.end(), follower);

  if (it != followers.end())
    (*it).incrementFrequency();

  else
    followers.push_back(follower);
}

std::ostream& operator<<(std::ostream& os, const WordList& wl)
{
  os<<"(base word: "<<wl.baseWord<<")";

  for (int i = 0; i < wl.followers.size(); i++)
    os<<"->("<<wl.followers[i]<<")";

  return os;
}
