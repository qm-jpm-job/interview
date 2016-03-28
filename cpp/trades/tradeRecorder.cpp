#include <algorithm>
#include <exception>
#include <boost/lexical_cast.hpp>

#include "tradeRecorder.h"

using std::pair;
using std::runtime_error;

using boost::posix_time::microsec_clock;

Trade::Trade (TradeOperation Operation, ptime TimeOfTrade, double PricePaid, double Quantity) {
  operation = Operation;
  timeOfTrade = TimeOfTrade;
  pricePaid = PricePaid;
  quantity = Quantity;
}

TradeRecorder::TradeRecorder(ConfigurationReader& config) {
}

void TradeRecorder::Record(TradeOperation operation, const string & stockSymbol, double pricePaid, double quantity) {
  Record(microsec_clock::local_time(), operation, stockSymbol, pricePaid, quantity);
}

void TradeRecorder::Record(ptime timeOfTrade, TradeOperation operation, const string & stockSymbol, double pricePaid, double quantity) {
  ptime timeNow = microsec_clock::local_time() + (time_duration(0, 0, 1, 0));
  if (timeOfTrade > timeNow) {
    throw runtime_error("Time of trade cannot be in the future");
  }
  
  Trade newTrade(operation, timeOfTrade, pricePaid, quantity);

  // Add to connector table
  auto mapIterator = stockTradeConnectorTable.find(stockSymbol);
  if (mapIterator == stockTradeConnectorTable.end()) {
    stockTradeConnectorTable.insert(pair<string, vector<Trade*>>(string(stockSymbol), vector<Trade*>{&newTrade}));
  } else {
    stockTradeConnectorTable[stockSymbol].push_back(&newTrade);
  }
  // Add to data table
  tradeTable.push_back(newTrade);
  
  // Send a signal noting that a new trade has been added, with the trade data.
}

void TradeRecorder::Load(const string & stockSymbol, vector<Trade>& trades, ptime timeOfTrade, time_duration boundary, TradeLoadBoundaryDirection boundaryDirection) {
  auto connectorTableIterator = stockTradeConnectorTable.find(stockSymbol);
  if (connectorTableIterator == stockTradeConnectorTable.end()) {
    return;
  }

  vector<Trade*> stockTrades = stockTradeConnectorTable[stockSymbol];

  ptime lowerBoundary = timeOfTrade - boundary;
  ptime upperBoundary = timeOfTrade + boundary;

  auto tradesFoundIterator = find_if(stockTrades.begin(), stockTrades.end(),
                                     [boundaryDirection, &timeOfTrade, &lowerBoundary, &upperBoundary] (const Trade* tradeInVector) {
                                       switch (boundaryDirection) {
                                       case Lower: 
                                         return ((tradeInVector->getTimeOfTrade() > lowerBoundary) && (tradeInVector->getTimeOfTrade() < timeOfTrade));

                                       case Upper:
                                         return ((tradeInVector->getTimeOfTrade() > timeOfTrade) && (tradeInVector->getTimeOfTrade() < upperBoundary));

                                       case Both:
                                         return ((tradeInVector->getTimeOfTrade() > lowerBoundary) && (tradeInVector->getTimeOfTrade() < upperBoundary));
                                       }
                                     });

  while (tradesFoundIterator != stockTrades.end()) {
    // Copy create a new trade, don't use the one we have in the "database"
    trades.push_back(Trade(**tradesFoundIterator));
    
    tradesFoundIterator++;
  }
}
