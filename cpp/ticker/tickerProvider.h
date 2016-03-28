#ifndef JPMORGANI_ITICKERPROVIDER
#define JPMORGANI_ITICKERPROVIDER

#include <string>

using std::string;

class ITickerProvider {
 public:
  // Destructor won't be called, so use this to shutdown
  virtual void shutdown() = 0;
  
  virtual void loadConfig() const = 0;

  virtual string getName() const = 0;
  
  virtual double getTickerPrice (const string & symbol) = 0;
};

#endif
