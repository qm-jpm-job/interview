#ifndef JPMORGANI_CONFIGREADER
#define JPMORGANI_CONFIGREADER

#include <map>
#include <string>
#include <vector>

#include <boost/tuple/tuple.hpp>
#include <boost/variant/variant.hpp>

#include "IconfigReader.h"

using std::map;
using std::string;
using std::vector;

using boost::tuple;
using boost::variant;

class ConfigurationReader {
 private:
  map<ConfigFileType, IConfigReader*> configReaders;

  map<string, variant<int, string, vector<int>, vector<string>>> configEntries;

  void checkEntryExists(const string & entryName);
  
 public:
  ConfigurationReader();

  void loadConfig();
  void loadConfig(const tuple<ConfigFileType, ConfigFormatType, string>& config); 

  template <typename EntryType>
    EntryType getValue(const string& configEntry);
};
  
#endif
