#include "level.h"

namespace mlo {

uint64_t Level::Add(unsigned int word, unsigned int context) {
  uint64_t encoded = encode(word, context), index;


  if(grams_.count(encoded) == 0) {
    index = counts_.size();
    counts_.push_back(0);
    grams_[encoded] = index;
  } else {
    index = grams_[encoded];
  }

  counts_[index]++;

  return index; // return this context_id
}

uint64_t Level::count(uint64_t word, uint64_t context) {
  return counts_[grams_[encode(word, context)]];
}

uint64_t Level::encode(unsigned int word, unsigned int context) {
  return ((uint64_t)word << 34) + context; // ha!
}

}
