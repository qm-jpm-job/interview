#ifndef JPMORGANI_STOCKPRICECALCULATOR
#define JPMORGANI_STOCKPRICECALCULATOR

#include "tradeRecorder.h"
#include <vector>

template <class numericType>
struct calculateStockPrice {
  numericType operator() (const vector<Trade>& trades);
};

#endif
