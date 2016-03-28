#ifndef JPMORGANI_STOCKTICKER
#define JPMORGANI_STOCKTICKER

#include <string>
#include <vector>

#include "configReader.h"
#include "loader.h"
#include "stock.h"
#include "tickerProvider.h"

using std::string;
using std::vector;
  
class StockTicker {
 private:
  ITickerProvider* quoteProvider;
  
 public:
  StockTicker(ConfigurationReader& config, LibraryLoader& loader);
  
  double getTickerPrice (string symbol);

  template <class numericType>
    void getTickerPrice (Stock<numericType>& stock);

  template <class numericType>
    void getTickerPrice (vector<Stock<numericType>&>& stocks);
};

#endif
