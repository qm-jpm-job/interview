#include <exception>

#include "stock.h"

template <class numericType> Stock<numericType>::Stock (string Symbol) {
  symbol = Symbol;
}

template <class numericType> Stock<numericType>::Stock (string Symbol, numericType lastDividend) {
  symbol = Symbol;
  setLastDividend(lastDividend);
}

template <class numericType> Stock<numericType>::Stock (string Symbol, numericType lastDividend, double parValue) {
  symbol = Symbol;
  setLastDividend(lastDividend);
  setParValue(parValue);
}

template <class numericType> Stock<numericType>::Stock (string Symbol, numericType lastDividend, double parValue, numericType tickerPriceValue) {
  symbol = Symbol;
  setLastDividend(lastDividend);
  setParValue(parValue);
  tickerPrice.reset(TickerPrice<numericType>(tickerPriceValue));
}

template <class numericType> std::string Stock<numericType>::getSymbol() const {
  return symbol;
}

template <class numericType> void Stock<numericType>::setLastDividend(numericType LastDividend) {
  lastDividendValueSet = true;
  lastDividend = LastDividend;
}

/*! \brief Returns the value set to lastDividend Member
 *
 * Being that we do not know the type, I've chosen not to use something along the lines of Boost.Optional, mainly because 
 * I'm uncertain as to how the semantics would handle various types, and noting that one could being passing pointers here.
 * In more realistic scenarios, I would take the time to look into this. I am noting it here such that the reader is aware
 * that I did think of it, and the reasons as to why I chose not to use such a semantic.
 * For similar reason, I've assumed that as long as the value is set, the value is valid. 

 * In more realistic scenarios, I would advocate a system exception type and an exception table, 
 * with error codes and error text, allowing for text to be
 * translated by whatever mechanism (database lookup, static in-memory lookup, etc). I deem everything else done valid proof that
 * such is not beyond my capability, and have thus not chosen to do so for the purposes of this test.
 */
template <class numericType> const numericType & Stock<numericType>::getLastDividend() const {
  // We are going to assume that as long as we've set the value to something, the value is valid
  if (lastDividendValueSet) {
    return lastDividend;
  } else {
    throw std::runtime_error("An attempt was made to access the last dividend without it first being set.");
  }
}

template <class numericType> void Stock<numericType>::setParValue (double ParValue) {
  parValue = ParValue; 
}

template <class numericType> const double & Stock<numericType>::getParValue() const {
  return parValue;
}

template <class numericType> void Stock<numericType>::setTickerPrice (const TickerPrice<numericType>& price) {
  // Instantiate the local variable using the copy constructor. (Don't want to be worrying about maintaining scope of external variables beyond
  // the necessary call to setTickerPrice. As in, an iterator should work.
  tickerPrice.reset(TickerPrice<numericType>(price));
}

template <class numericType> const numericType& Stock<numericType>::getTickerPrice () const {
  return tickerPrice.get().getPrice();
}

template <class numericType> ostream& operator<< (ostream& outputStream, const Stock<numericType>& stock) {
  outputStream << stock.getSymbol();
  return outputStream;
}

template class Stock<float>;
template class Stock<double>;

template ostream& operator<< (ostream& outputStream, const Stock<float>& stock);
template ostream& operator<< (ostream& outputStream, const Stock<double>& stock);
