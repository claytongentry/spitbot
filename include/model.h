/*
 * model.h
 *
 * The model used to power the AI's decision making is an adjacency list
 * of all of Young Jeezy's lyrics.
 *
 * The adjacency list represents an n x n matrix of all the lyrics.
 * The element at the intersection of a word on the x-axis and a word
 * on the y axis represents the number of times the y-axis word preceded
 * the x-axis word in Jeezy's songs.
 */

#ifndef model_H
#define model_H

using namespace std;

class Model
{

  public:
    Model(string filename);
    void build_list();

};

#endif
