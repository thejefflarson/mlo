#include <sys/types.h>
#include <map>

#ifndef MLO_LEVEL_H
#define MLO_LEVEL_H

namespace MLO {

// A level stores word values and (software) pointers to associated higher level
// contexts
class Level {
 public:
  Level();
  ~Level();

  uint64_t Add(unsigned int word, unsigned int context) {
    uint64_t encoded = ((uint64_t)context << 34) + word; // ha!
    uint64_t index;

    if(gramz_.count(it) == 0) {
      counts.push_back(0);
      index = counts.size();
      gramz_[encoded] = index;
    } else {
      index = gramz_[encoded];
    }

    counts[index]++;

    return index; // generate next context_id
  };

  uint64_t getCount(uint64_t word, uint64_t context) {
    return gramz_[word][context];
  };

 private:
  Level(const Level&);
  void operator=(const Level&);

  std::vector<uint64_t> counts;
  std::map<uint64_t, uint64_t> gramz_;
// context_encoding, count_index
};

}

#endif
