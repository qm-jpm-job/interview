#include <algorithm>

#include "tickerPrice.h"
#include "stockTicker.h"

StockTicker::StockTicker(ConfigurationReader& config, LibraryLoader& loader) {
  string providerToUse = config.getValue<string>("NameOfTickerPriceProviderToUse");
  string loadFunction = config.getValue<string>("TickerPriceProviderInitFunction");

  quoteProvider = (ITickerProvider*)loader.GetInstance(providerToUse, loadFunction);
}

StockTicker::~StockTicker() {
  // Need to free the pointer
  quoteProvider->shutdown();
  free(quoteProvider);
}

double StockTicker::getTickerPrice (string symbol) {
  return quoteProvider->getTickerPrice(symbol);
}

template <class numericType> void StockTicker::getTickerPrice (Stock<numericType>& stock) {
  numericType price = (numericType)getTickerPrice(stock.getSymbol());

  stock.setTickerPrice(TickerPrice<numericType>(price));
}

template <class numericType> void StockTicker::getTickerPrice (vector<Stock<numericType>&>& stocks) {
  std::for_each(stocks.begin(), stocks.end(), [this] (Stock<numericType&>& inst) {
      getTickerPrice(inst);
    });
}

template void StockTicker::getTickerPrice (Stock<float>& stock);
template void StockTicker::getTickerPrice (Stock<double>& stock);
