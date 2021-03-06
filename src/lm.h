/*
   Silly trie implementation for n-gram language models.

   Uses Stupid Backoff (http://acl.ldc.upenn.edu/D/D07/D07-1090.pdf) for
   weighting.

   Stores the ngrams in successive levels, in last-rest order, because querying
   will be easier.

   It is useless to observe that the best volume of the many hexagons under my
   administration is entitled The Combed Thunderclap and another The Plaster
   Cramp and another Axaxaxas mlö.
*/


#ifndef MLO_LM_H
#define MLO_LM_H

#include "level.h"
#include "status.h"
#include <string>
#include <map>

namespace mlo {

class LM {
 public:
  LM(int grams);
  ~LM();

  Status Load(const std::string& filename);
  void query(const std::string& sentence);

 private:
  LM(const LM&);
  void operator=(const LM&);

  void AddSentence(const std::string& sentence);
  int grams_;
  Level *levels_;
  // Look up table to keep track of unigram ids
  std::map<std::string, int64_t> unigram_table_;

  typedef std::vector<std::string> Tokens;
  Tokens tokenize(const std::string& sentence);
};

}

#endif
