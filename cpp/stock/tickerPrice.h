#ifndef JPMORGANI_TICKERPRICE
#define JPMORGANI_TICKERPRICE

#include <boost/date_time/posix_time/posix_time_types.hpp>

using boost::posix_time::ptime;

template <class numericType> class TickerPrice {
 private:
  ptime tickerTime;
  numericType price;

 public:
  /** Represents the price for a stock at a given time
   *  Note, this is a completely read-only class after instantiation. That is, the price, once retrieved, cannot be changed.
   */
  TickerPrice (numericType Price);

  const ptime & getTime() const;
  const numericType & getPrice() const;
};

#endif
