#include "lm.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

namespace mlo {

LM::LM(int grams) :
  grams_(grams),
  levels_(new Level[grams_]),
  unigram_table_() { }

LM::~LM() { delete[] levels_; }

// TODO: both of the following should be in a builder class.
void LM::AddSentence(const std::string& sentence) {
  Tokens tokens = tokenize(sentence);

  Tokens::iterator it;
  int i;

  // push into levels
  for(i = 0, it = tokens.begin(); it < tokens.end(); it++, i++) {
    // set unigrams
    if(unigram_table_.count(*it) == 0)
      unigram_table_[*it] = unigram_table_.size();

    uint64_t unigram_id;

    // Insert i to i - grams_ into the levels.
    int backtrack = i - grams_;

    // Unigrams which are first up have a context id of zero
    uint64_t context_id = 0;
    for(int j = 0; i - j > backtrack && i - j > 0; j++) {
      unigram_id = unigram_table_[*(it - j)];
      context_id = levels_[j].Add(unigram_id, context_id);
    }
  }
}

Status LM::Load(const std::string& filename) {
  std::ifstream ifile;
  ifile.open(filename.c_str());

  if(ifile.fail()) return Status::IOError();

  while(ifile.good()) {
    std::string line;
    getline(ifile, line);
    AddSentence(line);
  }

  ifile.close();

  return Status::Ok();
}

LM::Tokens LM::tokenize(const std::string& sentence) {
  unsigned long offset = 0, poffset = 0, length = sentence.length();

  Tokens tokens;

  // split into tokens
  while(poffset < length){
    offset = sentence.find(" ", offset + 1);

    // We're at the last token
    if(offset == std::string::npos)
      offset = sentence.length();

    if(offset - poffset > 0)
      tokens.push_back(sentence.substr(poffset, offset - poffset));

    poffset = offset;
  }

  return tokens;
}

// For each token print out the S(w|w-gramz_) using stupid backoff
void LM::query(const std::string& sentence) {
  Tokens tokens = tokenize(sentence);
  Tokens::iterator it;

  for(it = tokens.begin(); it < tokens.end(); it++) {
    if(unigram_table_.count(*it) == 0) {
      std::cout << *it << ": <UNK>";
      continue;
    }

    for(int i = 0; i < grams_ && it + i < tokens.end(); i++) {
     // Range range = levels_[i].getRange(word_id);
    }
  }
}

}
