#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "commonStock.h"
#include "preferredStock.h"

#include "peRatioCalculator.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( PERatioCalculatorAcceptsRequiredTypes ) {
  calculatePERatio<CommonStock<float>>();
  calculatePERatio<CommonStock<double>>();

  calculatePERatio<PreferredStock<float>>();  
  calculatePERatio<PreferredStock<double>>();
}

// float should return float
BOOST_AUTO_TEST_CASE( PERatioCalculatorReturnsFloatWhenPassedFloat ) {
  CommonStock<float> stock("SYM", 1.0f, 0.0, 1.0f);

  auto value = calculatePERatio<float>()(stock);
  BOOST_REQUIRE( value == 1.0f );
}

// double should return double
BOOST_AUTO_TEST_CASE( PERatioCalculatorReturnsDoubleWhenPassedDouble ) {
  CommonStock<double> stock("SYM", 1.0, 0.0, 1.0);

  auto value = calculatePERatio<double>()(stock);
  BOOST_REQUIRE( value == 1.0 );  
}

// 0 ticker price returns 0
BOOST_AUTO_TEST_CASE( PERatioCalculatorReturnsZeroWhenPassedAZeroTickerPrice ) {
  CommonStock<float> stock("SYM", 1.0f, 0.0, 0.0f);

  auto value = calculatePERatio<float>()(stock);
  BOOST_REQUIRE( value == 0.0f );
}
                     
// 0 last dividend returns 0
BOOST_AUTO_TEST_CASE( PERatioCalculatorReturnsZeroWhenPassedAZeroDividend ) {
  CommonStock<float> stock("SYM", 0.0f, 0.0, 1.0f);

  auto value = calculatePERatio<float>()(stock);
  BOOST_REQUIRE( value == 0.0f );
}

// should return ticker price dividend by last dividend
BOOST_AUTO_TEST_CASE( PERatioComputesCorrectly ) {
  CommonStock<float> stock("SYM", 10.0f, 0.0, 10.0f);

  auto value = calculatePERatio<float>()(stock);
  BOOST_REQUIRE( value == 1.0f );
}

// par value shouldn't matter
BOOST_AUTO_TEST_CASE( PERatioCalculationIgnoresParValue ) {
  CommonStock<float> stock("SYM", 1.0f, 20.0, 1.0f);

  auto value = calculatePERatio<float>()(stock);
  BOOST_REQUIRE( value == 1.0f );  
}

// Should give them same values for common and preferred stock
BOOST_AUTO_TEST_CASE( PERatioCalculationIsTheSameForBothCommonAndPreferredStock ) {
  CommonStock<float> cStock("SYM", 13.0f, 20.0, 12.0f);
  PreferredStock<float> pStock("SYM", 0.0f, 13.0f, 20.0, 12.0f);
  
  auto cValue = calculatePERatio<float>()(cStock);
  auto pValue = calculatePERatio<float>()(pStock);

  BOOST_REQUIRE( cValue == pValue );  
}

// Should ignore fixed dividend for preferred stock in calculating
BOOST_AUTO_TEST_CASE( PERatioCalculationIgnoresFixedDividedValuleOfPreferredStocks ) { 
  PreferredStock<float> stock("SYM", 100.0f, 12.0f, 20.0, 12.0f);
  
  auto value = calculatePERatio<float>()(stock);

  BOOST_REQUIRE( value == 1.0f );  
}
