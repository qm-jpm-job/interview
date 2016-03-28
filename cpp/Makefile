CC=g++

compile_flags=-fpic -std=c++11
link_flags=-shared

BOOST_INC=-I/opt/local/include/
BOOST_LIB_DIR=-L/opt/local/lib/boost/

OUTPUT_DIR=./bin/
OUTPUT_FILENAME=interview_test

OBJECT_FILES=loader.o configReader.o iniConfigReader.o \
	tickerPrice.o stock.o commonStock.o preferredStock.o \
	dividendYieldCalculator.o floatCalculator.o doubleCalculator.o \
	stockTicker.o \
	tradeRecorder.o \
	main.o

DYNAMIC_LIBRARIES=randomValuesStockTickerProvider.o

LOADER_INC=-Iloader/
CONFIG_INC=-Iconfig/
STOCK_INC=-Istock/
TOOLS_INC=-Itools/
TICKER_INC=-Iticker/
TRADES_INC=-Itrades/

all: application dynamic_libraries unit_tests 

clean:
	@echo "Removing temporary files"
	@rm *~

unit_tests:
	@echo "Creating unit tests"

application: $(OBJECT_FILES)
	@echo "Linking application"
	@$(CC) -ldl $(OBJECT_FILES) -o $(OUTPUT_FILENAME)
	@mkdir -p $(OUTPUT_DIR)
	@mv $(OUTPUT_FILENAME) $(OUTPUT_DIR)

	@echo "Removing object files"
	@rm $(OBJECT_FILES)

dynamic_libraries: $(DYNAMIC_LIBRARIES)

main.o: main.cpp
	@echo "Compiling main"
	@$(CC) $(compile_flags) $(TICKER_INC) $(TOOLS_INC) $(STOCK_INC) $(CONFIG_INC) $(LOADER_INC) $(BOOST_INC) -c main.cpp 

randomValuesStockTickerProvider.o: ticker/randomValuesStockTickerProvider.cpp
	@echo "Compiling randomValues Ticker"
	@$(CC) $(compile_flags) $(TICKER_INC) $(STOCK_INC) $(BOOST_INC) -c ticker/randomValuesStockTickerProvider.cpp
	@$(CC) $(link_flags) randomValuesStockTickerProvider.o -o librandomValuesStockTickerProvider.so 
	@mv librandomValuesStockTickerProvider.so $(OUTPUT_DIR)
	@rm randomValuesStockTickerProvider.o

tradeRecorder.o: trades/tradeRecorder.cpp
	@echo "Compiling tradeRecorder"
	@$(CC) $(compile_flags) $(TRADES_INC) $(CONFIG_INC) $(STOCK_INC) $(LOADER_INC) $(BOOST_INC) -c trades/tradeRecorder.cpp

stockTicker.o: ticker/stockTicker.cpp
	@echo "Compiling stockTicker"
	@$(CC) $(compile_flags) $(TICKER_INC) $(CONFIG_INC) $(STOCK_INC) $(LOADER_INC) $(BOOST_INC) -c ticker/stockTicker.cpp

doubleCalculator.o: tools/doubleCalculator.cpp
	@echo "Compiling doubleCalculator"
	@$(CC) $(compile_flags) $(STOCK_INC) $(BOOST_INC) -c tools/doubleCalculator.cpp

floatCalculator.o: tools/floatCalculator.cpp
	@echo "Compiling floatCalculator"
	@$(CC) $(compile_flags) $(STOCK_INC) $(BOOST_INC) -c tools/floatCalculator.cpp

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

