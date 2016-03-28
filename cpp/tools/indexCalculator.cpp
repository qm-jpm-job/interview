#include <exception>
#include <cmath>
#include <numeric>

#include "indexCalculator.h"

using std::accumulate;
using std::pow;
using std::runtime_error;

template <class numericType> numericType calculateGBCEAllShareIndex<numericType>::operator() (const vector<numericType>& prices) {
  throw runtime_error("An attempt was made to calculate the stock index price providing an invalid type; as in not float, double or so on.");
};

template <> float calculateGBCEAllShareIndex<float>::operator() (const vector<float>& prices) {
  float PriceSum = accumulate(prices.begin(), prices.end(), 1.0f,
                              [] (float sum, const float& entry) {
                                return sum * entry;
                              });

  float vectorLength = (float)prices.size();
  float powerToRaiseTo = 1.0 / vectorLength;
  
  return pow(PriceSum, powerToRaiseTo);
}

template <> double calculateGBCEAllShareIndex<double>::operator() (const vector<double>& prices) {
  // Return the float op, cast to double
  vector<float> pricesAsFloat;
  for (auto pricesIterator = prices.begin(); pricesIterator != prices.end(); pricesIterator++) {
    pricesAsFloat.push_back((float)(*pricesIterator));
  }
  
  return (double)calculateGBCEAllShareIndex<float>()(pricesAsFloat);
}
