#include <sys/types.h>
#include <map>

#ifndef MLO_LEVEL_H
#define MLO_LEVEL_H

namespace MLO {

// A level stores word values and (software) pointers to associated higher level
// contexts
class Level {
 public:
  Level() : gramz_() {};
  ~Level();

  void Add(int64_t word, int64_t context) {
    gramz_[word][context] = gramz_[word][context]++;
  };

  int64_t getCount(int64_t word, int64_t context) {
    return gramz_[word][context];
  };

 private:
  Level(const Level&);
  void operator=(const Level&);


  typedef std::map<int64_t, int64_t> Record;
  std::map<int64_t, Record> gramz_;
};

}

#endif
