#include "preferredStock.h"

template <class numericType> PreferredStock<numericType>::PreferredStock (string symbol): CommonStock<numericType> (symbol) {
}

template <class numericType> PreferredStock<numericType>::PreferredStock (string symbol, numericType fixedDividend): CommonStock<numericType> (symbol) {
  setFixedDividend(fixedDividend);
}

template <class numericType> PreferredStock<numericType>::PreferredStock (string symbol, numericType fixedDividend, numericType lastDividend): CommonStock<numericType> (symbol, lastDividend) {
  setFixedDividend(fixedDividend);
}

template <class numericType> PreferredStock<numericType>::PreferredStock (string symbol, numericType fixedDividend, numericType lastDividend, double parValue) : CommonStock<numericType> (symbol, lastDividend, parValue) {
  setFixedDividend(fixedDividend);
}

template <class numericType> PreferredStock<numericType>::PreferredStock (string symbol, numericType fixedDividend, numericType lastDividend, double parValue, numericType tickerPrice): CommonStock<numericType> (symbol, lastDividend, parValue, tickerPrice) {
  setFixedDividend(fixedDividend);
}

template <class numericType> void PreferredStock<numericType>::setFixedDividend(numericType dividend) {
  fixedDividend = dividend;
}

template <class numericType> const numericType & PreferredStock<numericType>::getFixedDividend() const {
  return fixedDividend;
}

template class PreferredStock<float>;
template class PreferredStock<double>;
