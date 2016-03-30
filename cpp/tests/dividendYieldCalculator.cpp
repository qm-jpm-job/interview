#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "dividendYieldCalculator.h"
#include <boost/test/unit_test.hpp>
#include <exception>

// Check that all of our constructors work
BOOST_AUTO_TEST_CASE( DefinedNumericTypeShouldWork ) {
  calculateDividendYield<CommonStock<float>, float>();
  calculateDividendYield<CommonStock<double>, double>();

  calculateDividendYield<PreferredStock<float>, float>();  
  calculateDividendYield<PreferredStock<double>, double>();
}

// float template CommonStock return a float, 1.0f / 1.0f should return 1.0f
BOOST_AUTO_TEST_CASE( CommonStockFloatDividendYieldReturnsFloat ) {
  CommonStock<float> floatCommon ("SYM", 1.0f, 0.0, 1.0f);

  auto value = calculateDividendYield<CommonStock<float>, float>()(floatCommon);
  BOOST_REQUIRE(value == 1.0f);
}

// double template CommonStock return a double, 1.0 / 1.0 should return 1.0
BOOST_AUTO_TEST_CASE( CommonStockDoubleDividendYieldReturnsDouble) {
  CommonStock<double> doubleCommon ("SYM", 1.0, 0.0, 1.0);

  auto value = calculateDividendYield<CommonStock<double>, double>()(doubleCommon);
  BOOST_REQUIRE(value == 1.0);  
}

// 0 dividend should return 0
BOOST_AUTO_TEST_CASE( CommonStockDividendYieldCalculatorReturnsZeroWhenLastDividendIsZero ) {
  CommonStock<double> stock ("SYM", 0.0, 0.0, 1.0);

  auto value = calculateDividendYield<CommonStock<double>, double>()(stock);
  BOOST_REQUIRE(value == 0.0);  
}

// 0 ticker price should return an error
BOOST_AUTO_TEST_CASE( CommonStockDividendYieldCalculatorReturnsZeroWhenTickerPriceIsZero) {
  CommonStock<double> stock ("SYM", 1.0, 0.0, 0.0);

  calculateDividendYield<CommonStock<double>, double> calculator;
  BOOST_CHECK_THROW( calculator(stock), std::runtime_error ); 
}

// CommonStock should return lastDividend / tickerPrice
BOOST_AUTO_TEST_CASE( CommonStockDividendYieldCalculatorComputesCorrectly ) {
  CommonStock<double> stock ("SYM", 4.0, 0.0, 2.0);

  auto value = calculateDividendYield<CommonStock<double>, double>()(stock);
  auto check = stock.getLastDividend() / stock.getTickerPrice();
  BOOST_REQUIRE(value == check);    
}

// parValue should make no difference in CommonStock value
BOOST_AUTO_TEST_CASE( CommonStockDividendYieldCalculatorIgnoresParValue ) {
  CommonStock<double> stock ("SYM", 5.0, 2.0, 2.0);

  auto value = calculateDividendYield<CommonStock<double>, double>()(stock);
  auto check = stock.getLastDividend() / stock.getTickerPrice();
  BOOST_REQUIRE(value == check);    
}


// float template PreferredStock return a float
BOOST_AUTO_TEST_CASE( PreferredStockFloatDividendYieldReturnsFloat ) {
  PreferredStock<float> floatPreferred ("SYM", 1.0f, 0.0f, 1.0, 1.0f);

  auto value = calculateDividendYield<PreferredStock<float>, float>()(floatPreferred);
  BOOST_REQUIRE(value == 1.0f);  
}

// double template PreferredStock return a double
BOOST_AUTO_TEST_CASE( PreferredStockDoubleDividendYieldReturnsDouble) {
  PreferredStock<double> doublePreferred ("SYM", 1.0, 0.0, 1.0, 1.0);

  auto value = calculateDividendYield<PreferredStock<double>, double>()(doublePreferred);
  BOOST_REQUIRE(value == 1.0);  
}

// 0 fixed dividend should return 0
BOOST_AUTO_TEST_CASE( PreferredStockDividendYieldCalculatorReturnsZeroWhenFixedDividendIsZero ) {
  PreferredStock<float> floatPreferred ("SYM", 0.0f, 0.0f, 1.0, 1.0f);

  auto value = calculateDividendYield<PreferredStock<float>, float>()(floatPreferred);
  BOOST_REQUIRE(value == 0.0f);    
}

// 0 parValue should return 0
BOOST_AUTO_TEST_CASE( PreferredStockDividendYieldCalculatorReturnsZeroWhenParValueIsZero ) {
  PreferredStock<float> floatPreferred ("SYM", 1.0f, 0.0f, 0.0, 1.0f);

  auto value = calculateDividendYield<PreferredStock<float>, float>()(floatPreferred);
  BOOST_REQUIRE(value == 0.0f);  
}

// 0 ticker price should return an error
BOOST_AUTO_TEST_CASE( PreferredStockDividendYieldCalculatorReturnsZeroWhenTickerPriceIsZero ) {
  PreferredStock<float> floatPreferred ("SYM", 1.0f, 0.0f, 1.0, 0.0f);

  calculateDividendYield<PreferredStock<float>, float> calculator;
  BOOST_CHECK_THROW( calculator(floatPreferred), std::runtime_error );   
}

// CommonStock should return (fixedDividend * parValue) / tickerPrice
BOOST_AUTO_TEST_CASE( PreferredStockDividendYieldCalculatorComputesCorrectly ) {
  PreferredStock<float> stock ("SYM", 2.0f, 0.0f, 2.0, 2.0f);

  auto value = calculateDividendYield<PreferredStock<float>, float>()(stock);
  auto check = (stock.getFixedDividend() * stock.getParValue()) / stock.getTickerPrice();
  BOOST_REQUIRE(value == check);    
}
                     
// lastDividend should make no difference
BOOST_AUTO_TEST_CASE( PreferredStockDividendYieldCalculatorIgnoresLastDividendValue ) {
  PreferredStock<float> stock ("SYM", 2.0f, 20.0f, 2.0, 2.0f);

  auto value = calculateDividendYield<PreferredStock<float>, float>()(stock);
  auto check = (stock.getFixedDividend() * stock.getParValue()) / stock.getTickerPrice();
  BOOST_REQUIRE(value == check);  
}
