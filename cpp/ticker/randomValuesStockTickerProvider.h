#ifndef JPMORGANI_RANDOMVALUESSTOCKTICKERPROVIDER
#define JPMORGANI_RANDOMVALUESSTOCKTICKERPROVIDER

#include <map>
#include <string>

#include "stock.h"
#include "tickerProvider.h"

namespace RandomValueTickerProvider {
  struct Configuration {
    double TickerValueRange = 0.1;
    double DefaultMaxTickerPriceValue = 5000.0;
  };
}

using std::map;
using std::string;

using RandomValueTickerProvider::Configuration;

class RandomValuesTickerProvider : public ITickerProvider {
 private:
  const string PROVIDER_NAME = string("Random");
  Configuration config;
  
  // Let's not go completely crazy and mimic something akin to normal behaviour.
  // That is, following an initial ticker value, remember the previous one, and return a value within some
  // realistic range from it
  map<string, double> previousValues;

  void updateTickerPrice (double randomGeneratorSeedValue, const string & stockSymbol);
  void initializeTickerPrice (double randomGeneratorSeedValue, const string & stockSymbol);
    
 public:
  void shutdown() { }
  string getName() const { return PROVIDER_NAME; }
  
  void loadConfig() const;
  
  double getTickerPrice (const string& stockSymbol);
};

extern "C" {
  RandomValuesTickerProvider* LoadProvider() {
    return new RandomValuesTickerProvider;
  }
}

#endif
