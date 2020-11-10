#ifndef RetweetCollection_h
#define RetweetCollection_h

#include <Tweet.h>

class RetweetCollection {
  private:
  bool empty_;

  public:
  RetweetCollection() : empty_(true) {}
  bool isEmpty() const { return empty_; }

  unsigned int size() const { return isEmpty() ? 0 : 1; }

  void add(const Tweet& t) { empty_ = false; }

  void remove(const Tweet& t) {empty_ = true;}
};

#endif
