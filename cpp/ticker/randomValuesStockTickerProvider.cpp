#include <chrono>
#include <functional>
#include <random>

#include "randomValuesStockTickerProvider.h"

using std::pair;
using std::uniform_real_distribution;
using std::mt19937;

void RandomValuesTickerProvider::loadConfig() const {
  // Don't need to do anything here, as we have the config values set in code
}

void RandomValuesTickerProvider::updateTickerPrice (double seedValue, const string & stockSymbol) {
  double tickerPriceBound = previousValues[stockSymbol] * config.TickerValueRange;

  double tickerPriceLowerBound = previousValues[stockSymbol] - tickerPriceBound;
  double tickerPriceUpperBound = previousValues[stockSymbol] + tickerPriceBound;
    
  auto updatedPriceComputor = std::bind(uniform_real_distribution<double>(tickerPriceLowerBound, tickerPriceUpperBound), mt19937(seedValue));
  double updatedPrice = updatedPriceComputor();

  previousValues[stockSymbol] = updatedPrice;
}

void RandomValuesTickerProvider::initializeTickerPrice (double seedValue, const string & stockSymbol) {
  auto initialPriceComputor = std::bind(uniform_real_distribution<double>(0.1, config.DefaultMaxTickerPriceValue), mt19937(seedValue));
  double initialPrice = initialPriceComputor();
  
  previousValues.insert(pair<string, double>(stockSymbol, initialPrice));
}

double RandomValuesTickerProvider::getTickerPrice (const string & stockSymbol) {
  double seedValue = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  
  auto mapIterator = previousValues.find(stockSymbol);      
  if (mapIterator != previousValues.end()) {
    updateTickerPrice(seedValue, stockSymbol);
  } else {
    initializeTickerPrice(seedValue, stockSymbol);
  }

  return previousValues[stockSymbol];
}
