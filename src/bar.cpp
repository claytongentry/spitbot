/*
 * Bar implementation
 */

#include "bar.h"

/* Initializes the Bar object with information about the given line.
 * Calls a traceBack function to construct a response line.
 */
Bar::Bar(std::string given, Model* model, Nouncer* nouncer, Denouncer* denouncer) {
  updateLineStats(given, nouncer);
  std::string stressPattern;
  std::string rhymeStressPattern;

  stressPattern        = doStressPattern(given, nouncer);
  Rhymer* rhymer       = new Rhymer(nouncer, denouncer);
  std::string rhymeVal = rhymer->rhyme(lastGiven);
  rhymeStressPattern   = nouncer->doStressPattern(rhymeVal);
  Word* rhyme          = new Word(rhymeVal, rhymeStressPattern);

  fire = traceBack(rhyme, stressPattern, model, nouncer);

  delete rhymer;
  delete rhyme;
}

void Bar::spit() {
  std::cout << fire << std::endl;
}

Bar::~Bar(){}

/* Builds a response to the given line with the same number of syllables.*/
std::string Bar::traceBack(Word* base, std::string stressPattern, Model* m, Nouncer* n) {
  Word* _NULL_         = new Word("_NULL_", "");
  std::string response = base->getVal();

  stressPattern = truncStressPattern(stressPattern, base->getStressPattern());

  //construct response by traversing the adjacency-list
  while (stressPattern.length() > 0) {
    // find word in model
    WordList leadersList = filterStressPattern(m->find(base), stressPattern);
    Word* leader         = leadersList.pickLeader();

    if (leader->getVal() == "_NULL_") {
      leadersList = filterStressPattern(m->find(_NULL_), stressPattern);
      leader      = leadersList.pickLeader();
    }

    // TODO: It won't know what to do if no words match the stress pattern

    // add it to the response
    response = leader->getVal() + " " + response;

    // set leader as new base
    base = leader;

    stressPattern = truncStressPattern(stressPattern, base->getStressPattern());
  }

  delete _NULL_;

  return response;
}

/*
 * Filter leaders to only include options that match
 * the given stress pattern.
 */
WordList Bar::filterStressPattern(WordList* leadersList, std::string stressPattern) {
  WordList filteredLeaders(leadersList->getBase());
  std::vector<Word> leaders = leadersList->getLeaders();

  for (auto i = leaders.begin(); i != leaders.end(); ++i) {
    int stressPatternLen            = i->getStressPattern().length();
    std::string patternSlice        = stressPattern.substr(0, stressPatternLen);
    std::string leaderStressPattern = i->getStressPattern();

    if (leaderStressPattern == patternSlice) {
      filteredLeaders.addLeader(*i);
    }
  }

  return filteredLeaders;
}

/*
 * Parses the input line and updates member variables with
 * relevant characteristics:
 * - word count
 * - syllable count
 * - last word of line (for rhyming)
 */
void Bar::updateLineStats(std::string given, Nouncer* n) {
  std::istringstream ss(given);
  std::string last;

  int words = 0;
  int syls = 0;

  while (ss >> last) {
    words++;
    syls += n->getSylCount(last);
  }

  lastGiven = last;
}

std::string Bar::getLast() {
  return lastGiven;
}

std::string Bar::doStressPattern(std::string line, Nouncer* n) {
  std::string stressPattern;
  std::istringstream ss(line);
  std::string word;

  while (ss >> word) {
    std::string tmp = n->doStressPattern(word);
    stressPattern.insert(stressPattern.begin(), tmp.begin(), tmp.end());
  }

  return stressPattern;
}

std::string Bar::truncStressPattern(std::string givenStressPattern, std::string baseStressPattern) {
  int givenLen = givenStressPattern.length();
  int baseLen  = baseStressPattern.length();

  if (baseLen > givenLen) {
    return baseStressPattern;
  }
  else {
    return givenStressPattern.substr(baseLen, givenLen - baseLen);
  }
}
