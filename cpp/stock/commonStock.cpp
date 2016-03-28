#include "commonStock.h"

template <class numericType> CommonStock<numericType>::CommonStock (string symbol): Stock<numericType> (symbol) {
}

template <class numericType> CommonStock<numericType>::CommonStock (string symbol, numericType lastDividend): Stock<numericType> (symbol, lastDividend) {
}

template <class numericType> CommonStock<numericType>::CommonStock (string symbol, numericType lastDividend, double parValue): Stock<numericType> (symbol, lastDividend, parValue) {
}

template <class numericType> CommonStock<numericType>::CommonStock (string symbol, numericType lastDividend, double parValue, numericType tickerPrice): Stock<numericType> (symbol, lastDividend, parValue, tickerPrice) {
}

template class CommonStock<float>;
template class CommonStock<double>;
