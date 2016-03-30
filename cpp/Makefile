CC=g++

compile_flags=-fpic -std=c++11
link_flags=-shared

BOOST_INC=-I/opt/local/include/
BOOST_LIB_DIR=-L/opt/local/lib/
UNIT_TEST_LIBS=-lboost_unit_test_framework-mt

OUTPUT_DIR=./bin/
OUTPUT_FILENAME=interview_test

OBJECT_FILES=loader.o configReader.o iniConfigReader.o \
	tickerPrice.o stock.o commonStock.o preferredStock.o \
	dividendYieldCalculator.o peRatioCalculator.o indexCalculator.o \
	stockTicker.o \
	tradeRecorder.o \
	stockPriceCalculator.o \
	main.o

DYNAMIC_LIBRARIES=randomValuesStockTickerProvider.o

LOADER_INC=-Iloader/
CONFIG_INC=-Iconfig/
STOCK_INC=-Istock/
TOOLS_INC=-Itools/
TICKER_INC=-Iticker/
TRADES_INC=-Itrades/

all: application dynamic_libraries tests remove_obj
	@echo "Complilation has completed successfully."
	@echo "Please change to the output directory, ./bin/ by default, and execute the application"

remove_obj:
	@echo "Removing object files"
	@rm $(OBJECT_FILES)

clean:
	@echo "Removing all files except config"
	@rm $(OUTPUT_DIR)/$(OUTPUT_FILENAME)
	@rm $(OUTPUT_DIR)/*.o
	@rm *~

application: $(OBJECT_FILES)
	@echo "Linking application"
	@$(CC) -ldl $(OBJECT_FILES) -o $(OUTPUT_FILENAME)
	@mkdir -p $(OUTPUT_DIR)
	@mv $(OUTPUT_FILENAME) $(OUTPUT_DIR)

dynamic_libraries: $(DYNAMIC_LIBRARIES)

main.o: main.cpp
	@echo "Compiling main"
	@$(CC) $(compile_flags) $(TRADES_INC) $(TICKER_INC) $(TOOLS_INC) $(STOCK_INC) $(CONFIG_INC) $(LOADER_INC) $(BOOST_INC) -c main.cpp 

randomValuesStockTickerProvider.o: ticker/randomValuesStockTickerProvider.cpp
	@echo "Compiling randomValues Ticker"
	@$(CC) $(compile_flags) $(TICKER_INC) $(STOCK_INC) $(BOOST_INC) -c ticker/randomValuesStockTickerProvider.cpp
	@$(CC) $(link_flags) randomValuesStockTickerProvider.o -o librandomValuesStockTickerProvider.so 
	@mv librandomValuesStockTickerProvider.so $(OUTPUT_DIR)
	@rm randomValuesStockTickerProvider.o

stockPriceCalculator.o: tools/stockPriceCalculator.cpp
	@echo "Compiling stockPriceCalculator"
	@$(CC) $(compile_flags) $(TRADES_INC) $(TOOLS_INC) $(CONFIG_INC) $(STOCK_INC) $(BOOST_INC) -c tools/stockPriceCalculator.cpp

tradeRecorder.o: trades/tradeRecorder.cpp
	@echo "Compiling tradeRecorder"
	@$(CC) $(compile_flags) $(TRADES_INC) $(CONFIG_INC) $(STOCK_INC) $(LOADER_INC) $(BOOST_INC) -c trades/tradeRecorder.cpp

stockTicker.o: ticker/stockTicker.cpp
	@echo "Compiling stockTicker"
	@$(CC) $(compile_flags) $(TICKER_INC) $(CONFIG_INC) $(STOCK_INC) $(LOADER_INC) $(BOOST_INC) -c ticker/stockTicker.cpp

indexCalculator.o: tools/indexCalculator.cpp
	@echo "Compiling indexCalculator"
	@$(CC) $(compile_flags) $(STOCK_INC) $(BOOST_INC) -c tools/indexCalculator.cpp

peRatioCalculator.o: tools/peRatioCalculator.cpp
	@echo "Compiling peRatioCalculator"
	@$(CC) $(compile_flags) $(STOCK_INC) $(BOOST_INC) -c tools/peRatioCalculator.cpp

dividendYieldCalculator.o: tools/dividendYieldCalculator.cpp
	@echo "Compiling dividendYieldCalculator"
	@$(CC) $(compile_flags) $(STOCK_INC) $(BOOST_INC) -c tools/dividendYieldCalculator.cpp

preferredStock.o: stock/preferredStock.cpp
	@echo "Compiling preferredStock"
	@$(CC) $(compile_flags) $(BOOST_INC) -c stock/preferredStock.cpp

commonStock.o: stock/commonStock.cpp
	@echo "Compiling commonStock"
	@$(CC) $(compile_flags) $(BOOST_INC) -c stock/commonStock.cpp

stock.o: stock/stock.cpp
	@echo "Compiling stock"
	@$(CC) $(compile_flags) $(BOOST_INC) -c stock/stock.cpp

tickerPrice.o: stock/tickerPrice.cpp
	@echo "Compiling tickerPrice"
	@$(CC) $(compile_flags) $(BOOST_INC) -c stock/tickerPrice.cpp

configReader.o: config/configReader.cpp config/iniConfigReader.cpp
	@echo "Compiling configReader"
	@$(CC) $(compile_flags) $(CONFIG_INC) $(BOOST_INC) -c config/configReader.cpp config/iniConfigReader.cpp

iniConfigReader.o: config/iniConfigReader.cpp
	@echo "Compiling iniConfigReader"
	@$(CC) $(compile_flags) $(CONFIG_INC) $(BOOST_INC) -c config/iniConfigReader.cpp

loader.o: loader/loader.cpp
	@echo "Compiling library loader"
	@$(CC) $(compile_flags) $(BOOST_INC) -c loader/loader.cpp

# Unit tests
tests: commonStockTests \
	dividendYieldCalculatorTests indexCalculatorTests peRatioCalculatorTests stockPriceCalculatorTests
	@echo "Creating unit tests"

commonStockTests: commonStock.o stock.o tickerPrice.o
	@echo "Compiling commonStock tests"
	@$(CC) $(compile_flags) $(STOCK_INC) $(BOOST_INC) -c tests/commonStock.cpp -o commonStockTests.o
	@$(CC) $(BOOST_LIB_DIR) $(UNIT_TEST_LIBS) commonStockTests.o tickerPrice.o stock.o commonStock.o -o commonStockTests
	@echo "Running commonStock tests"
	@./commonStockTests
	@rm commonStockTests

dividendYieldCalculatorTests: dividendYieldCalculator.o preferredStock.o commonStock.o stock.o tickerPrice.o
	@echo "Compiling dividend yield calculator tests"
	@$(CC) $(compile_flags) $(TOOLS_INC) $(STOCK_INC) $(BOOST_INC) -c tests/dividendYieldCalculator.cpp -o dividendYieldCalculatorTests.o
	@$(CC) $(BOOST_LIB_DIR) $(UNIT_TEST_LIBS) dividendYieldCalculatorTests.o tickerPrice.o stock.o commonStock.o preferredStock.o dividendYieldCalculator.o -o dividendYieldCalculatorTests

	@echo "Running dividend yield calculation tests"
	@./dividendYieldCalculatorTests
	@rm dividendYieldCalculatorTests

indexCalculatorTests: indexCalculator.o preferredStock.o commonStock.o stock.o tickerPrice.o
	@echo "Compiling GBCE index calculator tests"
	@$(CC) $(compile_flags) $(TOOLS_INC) $(STOCK_INC) $(BOOST_INC) -c tests/indexCalculator.cpp -o indexCalculatorTests.o
	@$(CC) $(BOOST_LIB_DIR) $(UNIT_TEST_LIBS) indexCalculatorTests.o indexCalculator.o preferredStock.o tickerPrice.o stock.o commonStock.o -o indexCalculatorTests

	@echo "Running GBCE index calculator tests"
	@./indexCalculatorTests
	@rm indexCalculatorTests

peRatioCalculatorTests: peRatioCalculator.o preferredStock.o commonStock.o stock.o tickerPrice.o
	@echo "Compiling P/E Ratio calculator tests"
	@$(CC) $(compile_flags) $(TOOLS_INC) $(STOCK_INC) $(BOOST_INC) -c tests/peRatioCalculator.cpp -o peRatioCalculatorTests.o
	@$(CC) $(BOOST_LIB_DIR) $(UNIT_TEST_LIBS) peRatioCalculatorTests.o peRatioCalculator.o preferredStock.o tickerPrice.o stock.o commonStock.o -o peRatioCalculatorTests 

	@echo "Running P/E Ratio calculator tests"
	@./peRatioCalculatorTests
	@rm peRatioCalculatorTests

stockPriceCalculatorTests: stockPriceCalculator.o preferredStock.o commonStock.o stock.o tickerPrice.o tradeRecorder.o
	@echo "Compiling stock price calculator tests"
	@$(CC) $(compile_flags) $(CONFIG_INC) $(TRADES_INC) $(TOOLS_INC) $(STOCK_INC) $(BOOST_INC) -c tests/stockPriceCalculator.cpp -o stockPriceCalculatorTests.o
	@$(CC) $(BOOST_LIB_DIR) $(UNIT_TEST_LIBS) stockPriceCalculatorTests.o stockPriceCalculator.o preferredStock.o tradeRecorder.o tickerPrice.o stock.o commonStock.o -o stockPriceCalculatorTests

	@echo "Running stock price calculator tests"
	@./stockPriceCalculatorTests
	@rm stockPriceCalculatorTests



