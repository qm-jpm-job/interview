#ifndef JPMORGANI_COMMONSTOCK
#define JPMORGANI_COMMONSTOCK

#include "stock.h"

using std::string;

template <class numericType> class CommonStock : public Stock<numericType> {
 public:
  CommonStock (string symbol);
  CommonStock (string symbol, numericType lastDividend);
  CommonStock (string symbol, numericType lastDividend, double parValue);
  CommonStock (string symbol, numericType lastDividend, double parValue, numericType tickerPrice);
    
  StockType getStockType () { return StockType::Common; }
};

#endif
