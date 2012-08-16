#include <sys/types.h>
#include <map>
#include <vector>

#ifndef MLO_LEVEL_H
#define MLO_LEVEL_H

namespace mlo {

// A level stores word values and (software) pointers to associated higher level
// contexts
class Level {
 public:
  Level();
  ~Level();

  // TODO: move method definitions to level.cpp
  uint64_t Add(unsigned int word, unsigned int context) {
    uint64_t encoded = encode(word, context);
    uint64_t index;

    if(gramz_.count(encoded) == 0) {
      index = counts_.size();
      counts_.push_back(0);
      gramz_[encoded] = index;
    } else {
      index = gramz_[encoded];
    }

    counts_[index]++;

    return index; // return this context_id
  };

  uint64_t count(uint64_t word, uint64_t context) {
    return gramz_.count(encode(word, context));
  };

 private:
  Level(const Level&);
  void operator=(const Level&);

  std::vector<uint64_t> counts_;
  std::map<uint64_t, uint64_t> gramz_;
// context_encoding, count_index

  uint64_t encode(unsigned int word, unsigned int context){
    return ((uint64_t)context << 34) + word; // ha!
  }
};

}

#endif
