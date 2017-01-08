/*
 * Battle implementation
 */

#include "battle.h"

/* Initializes the Battle object with information about the given line.
 * Calls a traceBack function to construct a response line.
 */
Battle::Battle(std::string given, Model* model, Nouncer* nouncer, Denouncer* denouncer) {
  updateLineStats(given, nouncer);

  std::string stressPattern;
  std::string rhymeStressPattern;
  std::string rhymeName;

  stressPattern         = doStressPattern(given, nouncer);

  Rhymer rhymer(nouncer, denouncer);

  rhymeName             = rhymer.rhyme(lastGiven);
  rhymeStressPattern    = nouncer->doStressPattern(rhymeName);

  Word rhyme(rhymeName, rhymeStressPattern);

  fire = traceBack(rhyme, stressPattern, model, nouncer);

}

void Battle::spit() {
  std::cout << fire << std::endl;
}

Battle::~Battle(){}

/* Builds a response to the given line with the same number of syllables.*/
std::string Battle::traceBack(Word base, std::string stressPattern, Model* m, Nouncer* n) {
  Word _NULL_("_NULL_", "");
  std::string response = base.getName();

  stressPattern = truncStressPattern(stressPattern, base.getStressPattern());

  //construct response by traversing the adjacency-list
  while (stressPattern.length() > 0) {
    // find word in model
    WordList leadersList = filterStressPattern(m->find(base), stressPattern);
    Word leader         = leadersList.pickLeader();

    if (leader.getName()== "_NULL_") {
      leadersList = filterStressPattern(m->find(_NULL_), stressPattern);
      leader      = leadersList.pickLeader();
    }

    // TODO: It won't know what to do if no words match the stress pattern

    // add it to the response
    response = leader.getName()+ " " + response;

    // set leader as new base
    base = leader;

    stressPattern = truncStressPattern(stressPattern, base.getStressPattern());
  }

  return response;
}

/*
 * Filter leaders to only include options that match
 * the given stress pattern.
 */
WordList Battle::filterStressPattern(WordList* leadersList, std::string stressPattern) {
  WordList filteredLeaders(leadersList->getBase());
  std::vector<Word> leaders = leadersList->getLeaders();

  for (auto it = leaders.begin(); it != leaders.end(); ++it) {
    int stressPatternLen            = it->getStressPattern().length();
    std::string patternSlice        = stressPattern.substr(0, stressPatternLen);
    std::string leaderStressPattern = it->getStressPattern();

    if (leaderStressPattern == patternSlice) {
      filteredLeaders.addLeader(*it);
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
void Battle::updateLineStats(std::string given, Nouncer* n) {
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

std::string Battle::getLast() {
  return lastGiven;
}

std::string Battle::doStressPattern(std::string line, Nouncer* n) {
  std::string stressPattern;
  std::istringstream ss(line);
  std::string word;

  while (ss >> word) {
    std::string tmp = n->doStressPattern(word);
    stressPattern.insert(stressPattern.begin(), tmp.begin(), tmp.end());
  }

  return stressPattern;
}

std::string Battle::truncStressPattern(std::string givenStressPattern, std::string baseStressPattern) {
  int givenLen = givenStressPattern.length();
  int baseLen  = baseStressPattern.length();

  if (baseLen > givenLen) {
    return baseStressPattern;
  }
  else {
    return givenStressPattern.substr(baseLen, givenLen - baseLen);
  }
}
