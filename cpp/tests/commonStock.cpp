#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <commonStock.h>
#include <boost/test/unit_test.hpp>

// Check that all of our constructors work
BOOST_AUTO_TEST_CASE( CommonStockSymbolConstructorSetsAttribute )
{
  CommonStock<float> stock( "SYM" );
  BOOST_REQUIRE( stock.getSymbol().compare("SYM") == 0);
}

BOOST_AUTO_TEST_CASE( CommonStockSymbolLastDividendConstructorSetsAttributes )
{
  CommonStock<float> stock( "SYM", 1.0f );
  BOOST_REQUIRE( stock.getSymbol().compare("SYM") == 0);
  BOOST_REQUIRE( stock.getLastDividend() == 1.0f);  
}

BOOST_AUTO_TEST_CASE( CommonStockSymbolLastDividendParValueConstructorSetsAttributes )
{
  CommonStock<float> stock( "SYM", 1.0f, 2.0 );
  BOOST_REQUIRE( stock.getSymbol().compare("SYM") == 0);
  BOOST_REQUIRE( stock.getLastDividend() == 1.0f);
  BOOST_REQUIRE( stock.getParValue() == 2.0);  
}

BOOST_AUTO_TEST_CASE( CommonStockSymbolLastDividendParValueTickerPriceConstructorSetsAttributes )
{
  CommonStock<float> stock( "SYM", 1.0f, 2.0, 3.1f );
  BOOST_REQUIRE( stock.getSymbol().compare("SYM") == 0);
  BOOST_REQUIRE( stock.getLastDividend() == 1.0f);
  BOOST_REQUIRE( stock.getParValue() == 2.0);  
  BOOST_REQUIRE( stock.getTickerPrice() == 3.1f);    
}

// Make sure that we get common stock stockType
BOOST_AUTO_TEST_CASE( CommonStockIsOfTheRightType )
{
  CommonStock<float> stock( "SYM" );
  BOOST_REQUIRE( stock.getStockType() == Common );
}
