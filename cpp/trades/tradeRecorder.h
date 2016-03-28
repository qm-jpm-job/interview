#ifndef JPMORGANI_TRADERECORDER
#define JPMORGANI_TRADERECORDER

#include <string>
#include <map>
#include <vector>

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "configReader.h"
#include "stock.h"

using std::map;
using std::string;
using std::vector;


using boost::posix_time::ptime;
using boost::posix_time::time_duration;

enum TradeOperation {
  Buy,
  Sell
};

enum TradeLoadBoundaryDirection {
  Lower,
  Upper,
  Both
};

class Trade {
 private:
  TradeOperation operation;  
  ptime timeOfTrade;
  double unitPrice;
  double quantity;

 public:
  // Allowing overriding of time so that we can simulate 15 minutes
  Trade(TradeOperation, ptime, double, double);

  TradeOperation getOperation() const { return operation; }
  ptime getTimeOfTrade() const { return timeOfTrade; }
  double getUnitPrice() const { return unitPrice; }
  double getQuantity() const { return quantity; }
};

class TradeRecorder {
 private:
  // In memory store of all trades, serves as trade Table; no limits apply here.
  // This could be abstracted by a "MemoryTradeStorageProvider" type class, but no need to demonstrate that yet again
  vector<Trade> tradeTable;
  map<string, vector<Trade*>> stockTradeConnectorTable;
    
 public:
  TradeRecorder(ConfigurationReader& config);

  void Record(TradeOperation operation, const string & stockSymbol, double unitPrice, double quanity);

  void Record(ptime tradeTime, TradeOperation operation, const string & stockSymbol, double unitPrice, double quanity);
  
  // Loads all trades in the specified boundary
  void Load(const string & stockSymbol, vector<Trade>& trades, ptime timeOfTrade, time_duration boundary, TradeLoadBoundaryDirection boundaryDirection);

  int getTableSize() { return tradeTable.size(); }
};
#endif
