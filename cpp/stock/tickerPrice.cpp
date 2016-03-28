#include "tickerPrice.h"

using boost::posix_time::microsec_clock;

template <class numericType> TickerPrice<numericType>::TickerPrice (numericType Price) {
  tickerTime = microsec_clock::universal_time();
  price = Price;
}

template <class numericType> const ptime& TickerPrice<numericType>::getTime() const {
  return tickerTime;
}

template <class numericType> const numericType& TickerPrice<numericType>::getPrice() const {
  return price;
}

template class TickerPrice<float>;
template class TickerPrice<double>;
