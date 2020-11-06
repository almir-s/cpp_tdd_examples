#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <thread>

using ::testing::Eq;
using namespace testing;

class Soundex {
  private:
  std::string zeroPad(const std::string& word) { return word + "000"; }

  public:
  std::string encode(const std::string& word) { return zeroPad(word); }
};

class SoundexEncoding : public Test {
  public:
  Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
  ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
  ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

