#ifndef JPMORGANI_ITICKERPROVIDER
#define JPMORGANI_ITICKERPROVIDER

#include <string>

using std::string;

class ITickerProvider {
 public:
  virtual void loadConfig() const = 0;

  virtual string getName() const = 0;
  
  virtual double getTickerPrice (const string & symbol) = 0;
};

#endif
