#include <RetweetCollection.h>
#include <exception>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <stdexcept>

#include "Tweet.h"

using namespace ::testing;

class ARetweetCollection : public Test {
  public:
  RetweetCollection collection;
};

class ARetweetCollectionWithOneTweet : public Test {
  public:
  RetweetCollection collection;
  void SetUp() override { collection.add(Tweet()); }
};

TEST_F(ARetweetCollectionWithOneTweet, HasSizeOfOne) {
  ASSERT_THAT(collection.size(), Eq(1u));
}

TEST_F(ARetweetCollectionWithOneTweet, IsNoLongerEmpty) {
  ASSERT_FALSE(collection.isEmpty());
}

TEST_F(ARetweetCollection, IsEmptyWhenCreated) {
  ASSERT_TRUE(collection.isEmpty());
}

TEST_F(ARetweetCollection, HasSizeZeroWhenCreated) {
  ASSERT_THAT(collection.size(), Eq(0u));
}

TEST_F(ARetweetCollection, HasSizeOfOneAfterTweetAdded) {
  collection.add(Tweet());
  ASSERT_THAT(collection.size(), Eq(1u));
}

TEST_F(ARetweetCollection, IsNoLongerEmptyAfterTweetAdded) {
  collection.add(Tweet());
  ASSERT_FALSE(collection.isEmpty());
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

TEST_F(ARetweetCollection, RequireUserToStartWithAnAtSign) {
  std::string invalidUser("invalidUserName");
  ASSERT_THROW(Tweet t("ultra cool message", invalidUser), std::runtime_error);
}

TEST_F(ARetweetCollection, RequireUserToStartWithAnAtSignDifferentImpl) {
  std::string invalidUser("invalidUserName");
  try {
    Tweet t("coll msg", invalidUser);
    FAIL();
  } catch (const std::runtime_error& err) {
    ASSERT_STREQ("Invalid username", err.what());
  }
}
