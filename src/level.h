#include <sys/types.h>
#include <map>
#include <vector>

#ifndef MLO_LEVEL_H
#define MLO_LEVEL_H

namespace mlo {

// A level stores word values and (software) pointers to associated higher level
// contexts.
class Level {
 public:
  Level() : total_(0), counts_(), grams_() { }
  ~Level() { }

  // TODO: move method definitions to level.cpp
  uint64_t Add(unsigned int word, unsigned int context);
  uint64_t count(uint64_t word, uint64_t context);

 private:
  Level(const Level&);
  void operator=(const Level&);

  uint64_t total_;
  std::vector<uint64_t> counts_;

// context_encoding, count_index
  std::map<uint64_t, uint64_t> grams_;

  uint64_t encode(unsigned int word, unsigned int context);
};

}

#endif
