#include <gmock/gmock.h>
#include <portfolio.h>

using namespace ::testing;
using namespace boost::gregorian;

class APortfolio : public Test {
  public:
  static const std::string IBM;
  static const std::string SAMSUNG;
  Portfolio portfolio_;
};

const std::string APortfolio::IBM("IBM");
const std::string APortfolio::SAMSUNG("SAMSUNG");


TEST_F(APortfolio, IsEmptyWhenCreated) { ASSERT_TRUE(portfolio_.IsEmpty()); }

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
  portfolio_.Purchase(IBM, 1);
  ASSERT_FALSE(portfolio_.IsEmpty());
}

TEST_F(APortfolio, AnswersZeroForShareCountOfUnpurchasedSymbol) {
  ASSERT_THAT(portfolio_.ShareCount("AAPL"), Eq(0u));
}

TEST_F(APortfolio, AnswersShareCountForPurchasedSymbol) {
  portfolio_.Purchase(IBM, 2);
  ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(2u));
}

TEST_F(APortfolio, AnswersThePurchaseRecordForASinglePurchase) {
  date dateOfPurchase(2014, Mar, 17);
  portfolio_.Purchase(SAMSUNG, 5, dateOfPurchase);
  portfolio_.Purchase(SAMSUNG, 5);
  auto purchases = portfolio_.Purchases(SAMSUNG);
  auto purchase = purchases[0];
  ASSERT_THAT(purchase.ShareCount, Eq(5u));
  ASSERT_THAT(purchase.Date, Eq(dateOfPurchase));
}

