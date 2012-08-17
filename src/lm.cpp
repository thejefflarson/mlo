#include "lm.h"
#include <vector>
#include <fstream>
#include <string>

namespace mlo {

LM::LM(int grams) :
  grams_(grams),
  levels_(new Level[grams_]),
  unigram_table_() { }

LM::~LM(){ delete[] levels_; }

// TODO: both of the following should be in a builder class.
void LM::AddSentence(const std::string& sentence){
  std::vector<std::string> tokens;
  unsigned long offset = 0, noffset = 0;
  int i = 0;

  // split into tokens
  while((offset = sentence.find(" ", offset + 1)) != std::string::npos){
    noffset = sentence.find(" ", offset + 1);

    // We're at the last token
    if(noffset == std::string::npos) noffset = sentence.length();

    if(noffset - offset > 0)
      tokens.push_back(sentence.substr(offset, noffset - offset));
  }

  std::vector<std::string>::iterator it;

  // push into levels
  for(it = tokens.begin(); it < tokens.end(); it++, i++) {
    // set unigrams
    if(unigram_table_.count(*it) == 0)
      unigram_table_[*it] = unigram_table_.size();

    int64_t unigram_id = unigram_table_[*it];

    // Insert i to i - grams_ into the levels.
    int backtrack = i - grams_ > 0 ? i - grams_ : 0;

    // Unigrams which are first up have a context id of zero
    uint64_t context_id = 0;
    for(int j = backtrack; j >= i; j--){
      context_id = levels_[j].Add(unigram_id, context_id);
    }
  }
}

Status LM::Load(const std::string& filename){
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

void LM::query(const std::string& sentence){
  (void)sentence;
}

}
