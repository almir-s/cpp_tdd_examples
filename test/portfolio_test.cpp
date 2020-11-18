#include <gmock/gmock.h>
#include <portfolio.h>
#include <date_test_constants.h>


using namespace ::testing;
using namespace std;
using namespace boost::gregorian;

class APortfolio: public Test {
public:
   static const string IBM;
   static const string SAMSUNG;
   Portfolio portfolio_;

   void Purchase(
         const string& symbol, 
         unsigned int shareCount,
         const date& transactionDate=ArbitraryDate) {
      portfolio_.Purchase(symbol, shareCount, transactionDate);
   }

   void Sell(
         const string& symbol, 
         unsigned int shareCount,
         const date& transactionDate=ArbitraryDate) {
      portfolio_.Sell(symbol, shareCount, transactionDate);
   }

   void ASSERT_PURCHASE(
         PurchaseRecord& purchase, int shareCount, const date& transactionDate) {
      ASSERT_THAT(purchase.ShareCount, Eq(shareCount));
      ASSERT_THAT(purchase.Date, Eq(transactionDate));
   }
};

const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");

TEST_F(APortfolio, IsEmptyWhenCreated) {
   ASSERT_TRUE(portfolio_.IsEmpty());
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
   Purchase(IBM, 1);

   ASSERT_FALSE(portfolio_.IsEmpty());
}

TEST_F(APortfolio, AnswersZeroForShareCountOfUnpurchasedSymbol) {
   ASSERT_THAT(portfolio_.ShareCount("AAPL"), Eq(0u));
}

TEST_F(APortfolio, AnswersShareCountForPurchasedSymbol) {
   Purchase(IBM, 2);

   ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(2u));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
   ASSERT_THROW(Purchase(IBM, 0), ShareCountCannotBeZeroException);
}

TEST_F(APortfolio, AnswersShareCountForAppropriateSymbol) {
   Purchase(IBM, 5);
   Purchase(SAMSUNG, 10);

   ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(5u));
}

TEST_F(APortfolio, ShareCountReflectsAccumulatedPurchasesOfSameSymbol) {
   Purchase(IBM, 5);
   Purchase(IBM, 15);

   ASSERT_THAT(portfolio_.ShareCount(IBM), Eq(5u + 15));
}

TEST_F(APortfolio, ReducesShareCountOfSymbolOnSell)  {
   Purchase(SAMSUNG, 30);
   
   Sell(SAMSUNG, 13);

   ASSERT_THAT(portfolio_.ShareCount(SAMSUNG), Eq(30u - 13));
}

TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased) {
   ASSERT_THROW(Sell(SAMSUNG, 1), InvalidSellException);
}

TEST_F(APortfolio, AnswersThePurchaseRecordForASinglePurchase) {
   Purchase(SAMSUNG, 5, ArbitraryDate);

   auto purchases = portfolio_.Purchases(SAMSUNG);

   ASSERT_PURCHASE(purchases[0], 5, ArbitraryDate);
}

TEST_F(APortfolio, IncludesSalesInPurchaseRecords) {
   Purchase(SAMSUNG, 10);
   Sell(SAMSUNG, 5, ArbitraryDate);

   auto sales = portfolio_.Purchases(SAMSUNG);

   ASSERT_PURCHASE(sales[1], -5, ArbitraryDate);
}

TEST_F(APortfolio, ThrowsOnSellOfZeroShares) {
   ASSERT_THROW(Sell(IBM, 0), ShareCountCannotBeZeroException);
}

bool operator==(const PurchaseRecord& lhs, const PurchaseRecord& rhs) {
   return lhs.ShareCount == rhs.ShareCount && lhs.Date == rhs.Date;
}

TEST_F(APortfolio, SeparatesPurchaseRecordsBySymbol) {
   Purchase(SAMSUNG, 5, ArbitraryDate);
   Purchase(IBM, 1, ArbitraryDate);

   auto sales = portfolio_.Purchases(SAMSUNG);

   ASSERT_THAT(sales, ElementsAre(PurchaseRecord(5, ArbitraryDate)));
}

TEST_F(APortfolio, AnswersEmptyPurchaseRecordVectorWhenSymbolNotFound) {
   ASSERT_THAT(portfolio_.Purchases(SAMSUNG), Eq(vector<PurchaseRecord>()));
}

TEST_F(APortfolio, SupportsMultiplePurchaseRecordsOfSymbol) {
   Purchase(SAMSUNG, 4, ArbitraryDate);
   Purchase(SAMSUNG, 11, ArbitraryDate);

   auto sales = portfolio_.Purchases(SAMSUNG);

   ASSERT_THAT(sales, ElementsAre(
            PurchaseRecord(4, ArbitraryDate),
            PurchaseRecord(11, ArbitraryDate)
            ));
}
