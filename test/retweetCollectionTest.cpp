#include <RetweetCollection.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;

class ARetweetCollection : public Test {
  public:
  RetweetCollection collection;
};

TEST_F(ARetweetCollection, IsEmptyWhenCreated) {
  ASSERT_TRUE(collection.isEmpty());
}

TEST_F(ARetweetCollection, HasSizeZeroWhenCreated) {
  ASSERT_THAT(collection.size(), Eq(0u));
}

TEST_F(ARetweetCollection, IsNoLongerEmptyAfterTweetAdded) {
  collection.add(Tweet());
  ASSERT_THAT(collection.size(), Eq(1u));
}

TEST_F(ARetweetCollection, DecreasesSizeAfterRemovingTweet) {
  collection.add(Tweet());
  collection.remove(Tweet());
  ASSERT_THAT(collection.size(), Eq(0u));
}

TEST_F(ARetweetCollection, IsEmptyAfterRemovingTweet) {
  collection.add(Tweet());
  collection.remove(Tweet());
  ASSERT_TRUE(collection.isEmpty());
}
