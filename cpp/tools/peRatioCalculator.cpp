#include "peRatioCalculator.h"

template <class numericType> numericType calculatePERatio<numericType>::operator() (const Stock<numericType>& stock) {
  if ((stock.getTickerPrice() == 0) || (stock.getLastDividend() == 0)) {
    return (numericType)0;
  }
  
  return (numericType)(stock.getTickerPrice()/stock.getLastDividend());
}

template class calculatePERatio<float>;
template class calculatePERatio<double>;
