#ifndef PURCHASE_RECORD_H
#define PURCHASE_RECORD_H

#include <boost/date_time/gregorian/gregorian_types.hpp>

struct PurchaseRecord {
   PurchaseRecord(int shareCount, const boost::gregorian::date& date)
      : ShareCount(shareCount)
      , Date(date) {
   }
   int ShareCount;
   boost::gregorian::date Date;
};

#endif

