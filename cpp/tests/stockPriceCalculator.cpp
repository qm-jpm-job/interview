#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "stockPriceCalculator.h"
#include <boost/test/unit_test.hpp>
#include <vector>

using std::vector;

BOOST_AUTO_TEST_CASE( StockPriceCalculatorIsAvailableForRequiredTypes ) {
  calculateStockPrice<float>();
  calculateStockPrice<double>();
}

// float should return float
BOOST_AUTO_TEST_CASE( StockPriceCalculatorReturnsFloatWhenPassedFloat ) {
  vector<Trade> trades;
  trades.push_back(Trade(Buy, 1.0, 10.0));

  auto value = calculateStockPrice<float>()(trades);
  BOOST_REQUIRE( value == 1.0f );
}

// double should return double
BOOST_AUTO_TEST_CASE( StockPriceCalculatorReturnsDoubleWhenPassedDouble ) {
  vector<Trade> trades;
  trades.push_back(Trade(Buy, 1.0, 10.0));

  auto value = calculateStockPrice<double>()(trades);
  BOOST_REQUIRE( value == 1.0 );  
}

// empty vector of trades passed should return 0
BOOST_AUTO_TEST_CASE( StockPriceCalculatorReturnsZeroWhenPassedAnEmptyList ) {
  vector<Trade> trades;

  auto value = calculateStockPrice<float>()(trades);
  BOOST_REQUIRE( value == 0.0f );  
}

// trades with 0 unit prices should return 0
BOOST_AUTO_TEST_CASE( StockPriceCalculatorReturnsZeroWhenUnitPricesAreZero ) {
  vector<Trade> trades;
  trades.push_back(Trade(Buy, 0.0, 10.0));

  auto value = calculateStockPrice<float>()(trades);
  BOOST_REQUIRE( value == 0.0f );  
}

// trades with 0 quantity should return 0
BOOST_AUTO_TEST_CASE( StockPriceCalculatorReturnsZeroWhenAllQuantitiesAreZero ) {
  vector<Trade> trades;
  trades.push_back(Trade(Buy, 1.0, 0.0));

  auto value = calculateStockPrice<float>()(trades);
  BOOST_REQUIRE( value == 0.0f );    
}

// value should equal sum of (numTrades * UnitPrice) divided by sum (numTrades)
// (1 * 10) + (1 * 10) = 20
// 10 + 10 = 20
// 20 / 20 = 1
BOOST_AUTO_TEST_CASE( StockPriceCalculatorComputesCorrectly ) {
  vector<Trade> trades;
  trades.push_back(Trade(Buy, 1.0, 10.0));
  trades.push_back(Trade(Buy, 1.0, 10.0));  

  auto value = calculateStockPrice<float>()(trades);
  BOOST_REQUIRE( value == 1.0f );
}

// trade sell should make no difference to price
BOOST_AUTO_TEST_CASE( StockPriceCalcultorShouldIgnoreTradeType_SellTypeCheck ) {
  vector<Trade> trades;
  trades.push_back(Trade(Sell, 1.0, 10.0));
  trades.push_back(Trade(Buy, 1.0, 10.0));  

  auto value = calculateStockPrice<float>()(trades);
  BOOST_REQUIRE( value == 1.0f );  
}
