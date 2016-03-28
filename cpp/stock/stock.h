#ifndef JPMORGANI_STOCK
#define JPMORGANI_STOCK

#include <boost/optional.hpp>

#include <iostream>
#include <string>
#include "tickerPrice.h"

using std::string;
using std::ostream;

using boost::optional;

/** Types of stock
 *
 *  Although operations are implemented noting the class type, we may still need to know what type the stock is
 *  based on something other than class definition. That is, I don't want to do a 'typeof' to know what type we are
 *  working with. 
 */
enum StockType {
  Common,
  Preferred
};
  
template <class numericType> class Stock {
 private:
  string symbol;

  bool lastDividendValueSet = false;
  numericType lastDividend;

  // Use optional so that we don't have to instantiate this when instantiating the class
  optional<TickerPrice<numericType>> tickerPrice;
  double parValue;
  
 public:
  /** Constructor
   *  Don't create stock without a symbol
   */
  Stock (string symbol);
  Stock (string symbol, numericType lastDividend);
  Stock (string symbol, numericType lastDividend, double parValue);
  Stock (string symbol, numericType lastDividend, double parValue, numericType tickerPrice);
    
  virtual StockType getStockType() = 0;

  string getSymbol() const;

  void setLastDividend (numericType LastDividend);
  const numericType & getLastDividend () const;

  void setTickerPrice (const TickerPrice<numericType>& tickerPrice);
  const numericType & getTickerPrice() const;
  
  void setParValue (double ParValue);
  const double & getParValue() const;

  template <class stockNumericType>
  friend ostream& operator<< (ostream& outputStream, const Stock<stockNumericType>& stock);
};

#endif
