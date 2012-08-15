#include "lm.h"
#include <vector>

namespace mlo {

LM::LM(int grams) {
  levels_ = new Level[grams];
  grams_  = grams;
};

LM::~LM(){
  delete[] levels_;
};

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
    int iterations = grams;
  }

  return Status.ok();
};

Status LM::Load(const std::string& filename){
  ifstream ifile(filename);

  if(ifile.fail()) return Status.IoError();

  while(ifile.good())
    AddSentence(ifile.getline());

  ifs.close();

  return Status.ok();
};

void query(const std::string& sentence){

};

}
