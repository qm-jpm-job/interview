#include "dividendYieldCalculator.h"

#include <exception>

using std::runtime_error;

template <class stockType, class numericType> numericType calculateDividendYield<stockType, numericType>::operator() (const stockType& stock) {
  throw runtime_error("An attempt was made to calculate the dividend ratio for a stock of invalid type, aka not CommonStock or PreferredStock or so on.");
}

// Implementor for common stock
template <class numericType> numericType calculateDividendYield<CommonStock<numericType>, numericType>::operator() (const CommonStock<numericType>& stock) {
  auto lastDividend = stock.getLastDividend();
  if (lastDividend == 0) {
    return (numericType)0;
  }
  
  auto tickerPrice = stock.getTickerPrice();
  if (tickerPrice == 0) {
    // If this is a valid case, then we should just return 0
    throw runtime_error("The ticker price for the given stock was zero when trying to calculate the dividend yield");
  }
  
  auto result = lastDividend / tickerPrice;
  return result;
}

// Implementor for preferred stock
template <class numericType> numericType calculateDividendYield<PreferredStock<numericType>, numericType>::operator() (const PreferredStock<numericType>& stock) {
  auto fixedDividend = stock.getFixedDividend();
  double parValue = stock.getParValue();
  if ((fixedDividend == 0) || (parValue == 0)) {
    return (numericType)0;
  }

  auto tickerPrice = stock.getTickerPrice();
  if (tickerPrice == 0) {
    // Once again, if this is a valid case, then we should just return 0
    throw runtime_error("The ticker price for the given stock was zero when trying to calculate the dividend yield");
  }

  auto result = (fixedDividend * parValue) / tickerPrice;
  return result;
}

template class calculateDividendYield<CommonStock<float>, float>;
template class calculateDividendYield<CommonStock<double>, double>;

template class calculateDividendYield<PreferredStock<float>, float>;
template class calculateDividendYield<PreferredStock<double>, double>;

