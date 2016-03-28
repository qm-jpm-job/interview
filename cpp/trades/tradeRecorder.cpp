#include <algorithm>
#include <exception>
#include <boost/lexical_cast.hpp>

#include "tradeRecorder.h"

using std::pair;
using std::runtime_error;

using boost::posix_time::microsec_clock;

Trade::Trade (TradeOperation Operation, ptime TimeOfTrade, double UnitPrice, double Quantity) {
  operation = Operation;
  timeOfTrade = TimeOfTrade;
  unitPrice = UnitPrice;
  quantity = Quantity;
}

TradeRecorder::TradeRecorder(ConfigurationReader& config) {
}

void TradeRecorder::Record(TradeOperation operation, const string & stockSymbol, double unitPrice, double quantity) {
  Record(microsec_clock::universal_time(), operation, stockSymbol, unitPrice, quantity);
}

void TradeRecorder::Record(ptime timeOfTrade, TradeOperation operation, const string & stockSymbol, double unitPrice, double quantity) {
  ptime timeNow = microsec_clock::universal_time() + (time_duration(0, 0, 1, 0));
  if (timeOfTrade > timeNow) {
    throw runtime_error("Time of trade cannot be in the future");
  }
  
  Trade newTrade(operation, timeOfTrade, unitPrice, quantity);

  // Add to data table
  tradeTable.push_back(newTrade);

  // Add to connector table
  auto mapIterator = stockTradeConnectorTable.find(stockSymbol);
  if (mapIterator == stockTradeConnectorTable.end()) {
    stockTradeConnectorTable.insert(pair<string, vector<Trade*>>(string(stockSymbol), vector<Trade*> {&tradeTable.back()}));
  } else {
    stockTradeConnectorTable[stockSymbol].push_back(&tradeTable.back());
  }  
}

void TradeRecorder::Load(const string & stockSymbol, vector<Trade>& trades, ptime timeOfTrade, time_duration boundary, TradeLoadBoundaryDirection boundaryDirection) {
  auto connectorTableIterator = stockTradeConnectorTable.find(stockSymbol);
  if (connectorTableIterator == stockTradeConnectorTable.end()) {
    return;
  }

  vector<Trade*> stockTrades = stockTradeConnectorTable[stockSymbol];
  
  ptime lowerBoundary = timeOfTrade - boundary;
  ptime upperBoundary = timeOfTrade + boundary;

  for_each(stockTrades.begin(), stockTrades.end(),
           [&trades, boundaryDirection, &timeOfTrade, &lowerBoundary, &upperBoundary] (const Trade* tradeInVector) {
             switch (boundaryDirection) {
             case Lower:                                       
               if ((tradeInVector->getTimeOfTrade() > lowerBoundary) && (tradeInVector->getTimeOfTrade() < timeOfTrade)) {
                 trades.push_back(Trade(*tradeInVector));
               }
               break;
               
             case Upper:
               if ((tradeInVector->getTimeOfTrade() > timeOfTrade) && (tradeInVector->getTimeOfTrade() < upperBoundary)) {
                 trades.push_back(Trade(*tradeInVector));
               }
               break;
               
             case Both:
               if ((tradeInVector->getTimeOfTrade() > lowerBoundary) && (tradeInVector->getTimeOfTrade() < upperBoundary)) {
                 trades.push_back(Trade(*tradeInVector));
               }
               break;
             }
           });    
}
