#include "peRatioCalculator.h"

template <class numericType> numericType calculatePERatio<numericType>::operator() (const Stock<numericType>& stock) {
  return (numericType)(stock.getTickerPrice()/stock.getLastDividend());
}

template class calculatePERatio<float>;
template class calculatePERatio<double>;
