#include "lm.h"
#include <vector>
#include <fstream>

namespace mlo {

LM::LM(int grams) {
  // subtract one for the unigram table
  grams_    = grams - 1;
  levels_   = new Level[grams_];
};

LM::~LM(){
  delete[] levels_;
};


// TODO: both of the following should be in a builder class.
void LM::AddSentence(const std::string& sentence){
  std::vector<std::string> tokens;
  int offset, noffset = 0, i = 0;

  // split into tokens
  while((offset = sentence.find_first_of(" ", offset)) != std::string::npos){
    noffset = sentence.find_first_of(" ", offset);

    // We're at the last token
    if(noffset == std::string::npos) noffset = sentence.length();

    if(noffset - offset > 0)
      tokens.push_back(sentence.substr(offset, noffset - offset));
  }

  std::vector<std::string>::iterator it;

  // push into levels
  for(it = tokens.begin(); it < tokens.end(); it++, i++) {
    // set unigram
    if(unigram_table_.count(it) == 0)
      unigram_table_[it] = unigram_table_.length();

    int64t_t unigram_id = unigram_table_[it];

    // Insert i to i - grams_ into the levels.
    int backtrack = i - grams_ > 0 ? i - grams_ : 0;
    uint64_t context_id = unigram_id;
    for(int j = i; j < backtrack; j++){
      context_id = levels_[j].add(it, context_id);
    }
  }

  return Status.ok();
};

Status LM::Load(const std::string& filename){
  std::ifstream ifile(filename);

  if(ifile.fail()) return Status.IoError();

  while(ifile.good())
    AddSentence(ifile.getline());

  ifs.close();

  return Status.ok();
};

void query(const std::string& sentence){

};

}
