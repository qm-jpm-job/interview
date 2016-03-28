#ifndef JPMORGANI_PREFERREDSTOCK
#define JPMORGANI_PREFERREDSTOCK

#include "commonStock.h"

template <class numericType> class PreferredStock : public CommonStock<numericType> {
 private:
  numericType fixedDividend;
  
 public:
  PreferredStock (string symbol);
  PreferredStock (string symbol, numericType fixedDividend);
  PreferredStock (string symbol, numericType fixedDividend, numericType lastDividend);
  PreferredStock (string symbol, numericType fixedDividend, numericType lastDividend, double parValue);
  PreferredStock (string symbol, numericType fixedDividend, numericType lastDividend, double parValue, numericType tickerPrice);

  void setFixedDividend (numericType dividend);
  const numericType & getFixedDividend() const;
};

#endif
