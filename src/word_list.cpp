/*
 * WordList implementation
 */

#include <iostream>
#include <algorithm>
#include "word_list.h"

/*
 * Instantiates a new WordList with given base_word
 */
WordList::WordList(Word w)
{
  base_word = w;
}

/*
 * Returns base word
 */
Word& WordList::get_base()
{
  return base_word;
}

/*
 * Returns followers
 */
std::vector<Word>& WordList::get_followers()
{
  return followers;
}

/*
 * Checks if 'follower' is already in 'followers[]'
 * Otherwise adds follower to followers[]
 */
void WordList::add_follower(Word follower)
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
  os<<"(base word: "<<wl.base_word<<")";

  for (int i = 0; i < wl.followers.size(); i++)
    os<<"->("<<wl.followers[i]<<")";

  return os;
}
