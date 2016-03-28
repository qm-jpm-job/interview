#include <iostream>
#include <boost/tuple/tuple.hpp>

#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "config/configReader.h"

#include "stock/commonStock.h"
#include "stock/preferredStock.h"

#include "tools/dividendYieldCalculator.h"

#include "ticker/stockTicker.h"

#include "trades/tradeRecorder.h"

using namespace std;

using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::microsec_clock;

// Create common stock
CommonStock<float> teaStock ("TEA", 0, 100);
CommonStock<float> popStock ("POP", 8, 100);
CommonStock<float> aleStock ("ALE", 23, 60);
CommonStock<float> joeStock ("JOE", 13, 250);
  
// Create preferred stock
PreferredStock<float> ginStock ("GIN", 0.02, 8, 100);

// Update all ticker prices
void update_ticker_prices(StockTicker& stockTicker) {
  stockTicker.getTickerPrice(teaStock);
  stockTicker.getTickerPrice(popStock);
  stockTicker.getTickerPrice(aleStock);
  stockTicker.getTickerPrice(joeStock);
  stockTicker.getTickerPrice(ginStock);
}

void calculate_dividend_yields() {
  cout << "Dividend yields" << endl;
  cout << teaStock << "\t" << calculateDividendYield<CommonStock<float>, float>()(teaStock) << endl;
  cout << popStock << "\t" << calculateDividendYield<CommonStock<float>, float>()(popStock) << endl;
  cout << aleStock << "\t" << calculateDividendYield<CommonStock<float>, float>()(aleStock) << endl;
  cout << joeStock << "\t" << calculateDividendYield<CommonStock<float>, float>()(joeStock) << endl;
  cout << ginStock << "\t" << calculateDividendYield<PreferredStock<float>, float>()(ginStock) << endl;
}

void make_random_purchase(TradeRecorder& tradeRecorder, ptime timeOfTrade) {
  int buyOrSell = rand() % 2;
  TradeOperation op = (buyOrSell) ? Buy : Sell;
  
  int quantity = rand() % 1000;
  int share = rand() % 5;

  switch (share) {
  case 0:
    tradeRecorder.Record(timeOfTrade, op, teaStock.getSymbol(), (double)teaStock.getTickerPrice() * quantity, quantity);
    break;
    
  case 1:
    tradeRecorder.Record(timeOfTrade, op, popStock.getSymbol(), (double)popStock.getTickerPrice() * quantity, quantity);
    break;
    
  case 2:
    tradeRecorder.Record(timeOfTrade, op, aleStock.getSymbol(), (double)aleStock.getTickerPrice() * quantity, quantity);
    break;
    
  case 3:
    tradeRecorder.Record(timeOfTrade, op, joeStock.getSymbol(), (double)joeStock.getTickerPrice() * quantity, quantity);
    break;
    
  case 4:
    tradeRecorder.Record(timeOfTrade, op, ginStock.getSymbol(), (double)ginStock.getTickerPrice() * quantity, quantity);
    break;
    
  default:
    return;
  }
}

int main(int argc, char** argv) {
  cout << "Running application" << endl;

  srand (std::chrono::high_resolution_clock::now().time_since_epoch().count());
  
  // Library loader
  LibraryLoader loader;
  
  // Load configuration
  ConfigurationReader config;
  config.loadConfig(boost::make_tuple<ConfigFileType, ConfigFormatType, string>(CF_FILE, CFMT_INI, "interview_test.config"));

  // Load global objects
  StockTicker stockTicker(config, loader);
  TradeRecorder tradeRecorder(config);
  
  // Get ticker prices
  update_ticker_prices(stockTicker);
  
  // Calculate dividend yields
  calculate_dividend_yields();
  
  // Calculate P/E Ratio

  // Simulate the recording of trades for 30 minutes
  // 10 trades a minute for 30 minutes
  int numberOfMinutes = 30;
  int numberOfSecondsBetweenTrades = 3; // Make sure this adds up, no tests of this
  int numberOfTradesPerMinute = 20;
  
  // Ugly inner loop, but no worries, only 300 runs
  for (int minute = 0; minute < numberOfMinutes; minute++) {
    // Start 1 minute ago
    ptime timeOfTrade = microsec_clock::universal_time() - time_duration(0, 1 + minute, 0, 0);
    
    for (int numOfTrades = 0; numOfTrades < numberOfTradesPerMinute / 2; numOfTrades++) {
      update_ticker_prices(stockTicker);
      
      make_random_purchase(tradeRecorder, timeOfTrade - time_duration(0, 0, 1 * numOfTrades));
    }
  }

  cout << "Total trades made: " << tradeRecorder.getTableSize() << endl;
  
  vector<Trade> popTrades;
  tradeRecorder.Load(popStock.getSymbol(), popTrades, microsec_clock::universal_time() - time_duration(0, 1, 0, 0), time_duration(0, 20, 0, 0), Lower);
  cout << "Number of popStock trades in the last 10 minutes: " << popTrades.size() << endl;
  
  // Calculate the stock price based on trades recorded for the past 15 minutes a few times

  // Calculate the GBCE all share index

  return 0;
}
