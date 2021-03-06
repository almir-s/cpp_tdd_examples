#include <portfolio.h>
#include <numeric>

using namespace std;
using namespace boost::gregorian;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

void Portfolio::Purchase(
      const string& symbol, unsigned int shareCount, const date& transactionDate) {
   Transact(symbol, shareCount, transactionDate);
}

void Portfolio::Sell(
      const string& symbol, unsigned int shareCount, const date& transactionDate) {
   if (shareCount > ShareCount(symbol)) throw InvalidSellException();
   Transact(symbol, -shareCount, transactionDate);
}

void Portfolio::Transact(
      const string& symbol, int shareChange, const date& transactionDate) {
   ThrowIfShareCountIsZero(shareChange);
   AddPurchaseRecord(symbol, shareChange, transactionDate);
}

void Portfolio::ThrowIfShareCountIsZero(int shareChange) const {
   if (0 == shareChange) throw ShareCountCannotBeZeroException();
}

void Portfolio::AddPurchaseRecord(
      const string& symbol, int shareChange, const date& date) {
   if (!ContainsSymbol(symbol))
      InitializePurchaseRecords(symbol);

   Add(symbol, {shareChange, date});
}

void Portfolio::InitializePurchaseRecords(const string& symbol) {
   purchaseRecords_[symbol] = vector<PurchaseRecord>();
   holdings_[symbol] = Holding();
}

void Portfolio::Add(const string& symbol, PurchaseRecord&& record) {
   purchaseRecords_[symbol].push_back(record);
   holdings_[symbol].Add(record);
}

bool Portfolio::ContainsSymbol(const string& symbol) const {
   return holdings_.find(symbol) != holdings_.end();
}

unsigned int Portfolio::ShareCount(const string& symbol) const {
   return Find<Holding>(holdings_, symbol).ShareCount();
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return Find<Holding>(holdings_, symbol).Purchases();
}
