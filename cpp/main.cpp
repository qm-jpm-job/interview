#include <iostream>
#include <boost/tuple/tuple.hpp>

#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "config/configReader.h"

#include "stock/commonStock.h"
#include "stock/preferredStock.h"

#include "tools/dividendYieldCalculator.h"
#include "tools/peRatioCalculator.h"
#include "tools/stockPriceCalculator.h"
#include "tools/indexCalculator.h"

#include "ticker/stockTicker.h"

#include "trades/tradeRecorder.h"

using namespace std;

using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::microsec_clock;

// forward declerations, functions are after int main(..)
void update_ticker_prices(StockTicker& stockTicker);
void calculate_dividend_yields();
void calculate_pe_ratios();
vector<double> stock_price_based_on_last_min(TradeRecorder& tradeRecorder, int minutes);
void make_random_purchase(TradeRecorder& tradeRecorder, ptime timeOfTrade);
  
// Create stock entries
CommonStock<float> teaStock ("TEA", 0, 100);
CommonStock<float> popStock ("POP", 8, 100);
CommonStock<float> aleStock ("ALE", 23, 60);
CommonStock<float> joeStock ("JOE", 13, 250);
PreferredStock<float> ginStock ("GIN", 0.02, 8, 100);

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
  calculate_pe_ratios();
  
  // Simulate the recording of trades for 30 minutes
  // 10 trades a minute for 30 minutes
  int numberOfMinutes = 30;
  int numberOfSecondsBetweenTrades = 3; // Make sure this adds up if modified, there are no tests of this as this is code to generate data / simulate.
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
    
  // Calculate the stock price based on trades recorded for the past 15 minutes
  vector<double> stockPrices = stock_price_based_on_last_min(tradeRecorder, 15);
  
  // Calculate the GBCE all share index
  cout << "GBCE All Share Index: " << calculateGBCEAllShareIndex<double>()(stockPrices) << endl;
  
  return 0;
}

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

void calculate_pe_ratios() {
  cout << "P/E Ratios" << endl;
  cout << teaStock << "\t" << calculatePERatio<float>()(teaStock) << endl;
  cout << popStock << "\t" << calculatePERatio<float>()(popStock) << endl;
  cout << aleStock << "\t" << calculatePERatio<float>()(aleStock) << endl;
  cout << joeStock << "\t" << calculatePERatio<float>()(joeStock) << endl;
  cout << ginStock << "\t" << calculatePERatio<float>()(ginStock) << endl;
}

vector<double> stock_price_based_on_last_min(TradeRecorder& tradeRecorder, int minutes) {
  vector<Trade> teaTrades;
  tradeRecorder.Load(teaStock.getSymbol(), teaTrades, microsec_clock::universal_time(), time_duration(0, minutes, 0, 0), Lower);
  cout << "Number of teaStock trades in the last " << minutes << " minutes: " << teaTrades.size() << endl;
    
  vector<Trade> popTrades;
  tradeRecorder.Load(popStock.getSymbol(), popTrades, microsec_clock::universal_time(), time_duration(0, minutes, 0, 0), Lower);
  cout << "Number of popStock trades in the last " << minutes << " minutes: " << popTrades.size() << endl;
  
  vector<Trade> joeTrades;
  tradeRecorder.Load(joeStock.getSymbol(), joeTrades, microsec_clock::universal_time(), time_duration(0, minutes, 0, 0), Lower);
  cout << "Number of joeStock trades in the last " << minutes << " minutes: " << joeTrades.size() << endl;
  
  vector<Trade> aleTrades;
  tradeRecorder.Load(aleStock.getSymbol(), aleTrades, microsec_clock::universal_time(), time_duration(0, minutes, 0, 0), Lower);
  cout << "Number of aleStock trades in the last " << minutes << " minutes: " << aleTrades.size() << endl;

  vector<Trade> ginTrades;
  tradeRecorder.Load(ginStock.getSymbol(), ginTrades, microsec_clock::universal_time(), time_duration(0, minutes, 0, 0), Lower);
  cout << "Number of ginStock trades in the last " << minutes << " minutes: " << ginTrades.size() << endl;

  double teaTradesStockPrice = calculateStockPrice<double>()(teaTrades);
  double popTradesStockPrice = calculateStockPrice<double>()(popTrades);
  double aleTradesStockPrice = calculateStockPrice<double>()(aleTrades);
  double joeTradesStockPrice = calculateStockPrice<double>()(joeTrades);
  double ginTradesStockPrice = calculateStockPrice<double>()(ginTrades);

  cout << minutes << " minutes based stock prices" << endl;
  cout << teaStock << "\t" << teaTradesStockPrice << endl;
  cout << popStock << "\t" << popTradesStockPrice << endl;
  cout << aleStock << "\t" << aleTradesStockPrice << endl;
  cout << joeStock << "\t" << joeTradesStockPrice << endl;
  cout << ginStock << "\t" << ginTradesStockPrice << endl;

  return vector<double> {teaTradesStockPrice, popTradesStockPrice, aleTradesStockPrice, joeTradesStockPrice, ginTradesStockPrice };
}

void make_random_purchase(TradeRecorder& tradeRecorder, ptime timeOfTrade) {
  int buyOrSell = rand() % 2;
  TradeOperation op = (buyOrSell) ? Buy : Sell;
  
  int quantity = rand() % 1000;
  int share = rand() % 5;

  switch (share) {
  case 0:
    tradeRecorder.Record(timeOfTrade, op, teaStock.getSymbol(), (double)teaStock.getTickerPrice(), quantity);
    break;
    
  case 1:
    tradeRecorder.Record(timeOfTrade, op, popStock.getSymbol(), (double)popStock.getTickerPrice(), quantity);
    break;
    
  case 2:
    tradeRecorder.Record(timeOfTrade, op, aleStock.getSymbol(), (double)aleStock.getTickerPrice(), quantity);
    break;
    
  case 3:
    tradeRecorder.Record(timeOfTrade, op, joeStock.getSymbol(), (double)joeStock.getTickerPrice(), quantity);
    break;
    
  case 4:
    tradeRecorder.Record(timeOfTrade, op, ginStock.getSymbol(), (double)ginStock.getTickerPrice(), quantity);
    break;
    
  default:
    return;
  }
}
