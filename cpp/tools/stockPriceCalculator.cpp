#include <exception>
#include <numeric>

#include "stockPriceCalculator.h"

using std::accumulate;
using std::runtime_error;

template <class numericType> numericType calculateStockPrice<numericType>::operator() (const vector<Trade>& trades) {
  throw runtime_error("An attempt was made to calculate the stock price returning an invalid type; as in not float, double or so on.");
}

template <> float calculateStockPrice<float>::operator() (const vector<Trade>& trades) {
  if (trades.size() == 0) {
    return 0.0f;
  }

  float QuantitySum = accumulate(trades.begin(), trades.end(), 0.0f,
                                 [] (float sumValue, const Trade& element) {
                                   return sumValue + (float)element.getQuantity();
                                 });
  if (QuantitySum == 0.0f) {
    return 0;
  }

  float TradePriceQuantitySum = accumulate(trades.begin(), trades.end(), 0.0f,
                                           [] (float sumValue, const Trade& element) {
                                             return sumValue + ((float)element.getUnitPrice() * (float)element.getQuantity());
                                           });
  if (TradePriceQuantitySum == 0.0f) {
    return 0;
  }
    
  return TradePriceQuantitySum / QuantitySum;
}

template <> double calculateStockPrice<double>::operator() (const vector<Trade>& trades) {
  // Floats are convertable to double inheritally
  return (double)calculateStockPrice<float>()(trades);
}
