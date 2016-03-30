#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "indexCalculator.h"
#include <boost/test/unit_test.hpp>
#include <vector>

using std::vector;

// Handles all available types
BOOST_AUTO_TEST_CASE( IndexCalculatorWorksForRequiredTypes ) {
  calculateGBCEAllShareIndex<float>();
  calculateGBCEAllShareIndex<double>();
}

// float should return a float
BOOST_AUTO_TEST_CASE( IndexCalculatorReturnsAFloatWhenPassedAFloat ) {
  vector<float> values {1.0f};

  auto value = calculateGBCEAllShareIndex<float>()(values);
  BOOST_REQUIRE(value == 1.0f);  
}

// double should return a double
BOOST_AUTO_TEST_CASE( IndexCalculatorReturnsADoubleWhenPassedADouble ) {
  vector<double> values {1.0};

  auto value = calculateGBCEAllShareIndex<double>()(values);
  BOOST_REQUIRE(value == 1.0);  
}

// an empty vector should return 0
BOOST_AUTO_TEST_CASE( IndexCalculatorReturnsZeroWhenItIsPassedAnEmptyList ) {
  vector<float> values;

  auto value = calculateGBCEAllShareIndex<float>()(values);
  BOOST_REQUIRE(value == 0.0f);    
}

// on 0 values should return 0
BOOST_AUTO_TEST_CASE( IndexCalculatorReturnsZeroWhenPassedZeroValues ) {
  vector<float> values {0.0f};

  auto value = calculateGBCEAllShareIndex<float>()(values);
  BOOST_REQUIRE(value == 0.0f);    
}

// should return nth root of (II entries)
BOOST_AUTO_TEST_CASE( IndexCalculatorComputesCorrectly ) {
  vector<float> values {2.0f, 2.0f};

  auto value = calculateGBCEAllShareIndex<float>()(values);
  BOOST_REQUIRE(value == 2.0f);      
}
