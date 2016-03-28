#ifndef JPMORGANI_ICONFIGREADER
#define JPMORGANI_ICONFIGREADER

#include <map>
#include <string>
#include <vector>

#include <boost/tuple/tuple.hpp>
#include <boost/variant/variant.hpp>

using std::string;
using std::map;
using std::vector;

using boost::tuple;
using boost::variant;

enum ConfigFileType {
  CF_MEMORY,
  CF_FILE,
  CF_SOAP,
  CF_REST,
  CF_HTTP
};
  
enum ConfigFormatType {
  CFMT_INI,
  CFMT_XML,
  CFMT_TAB,
  CFMT_JSON
};
  
class IConfigReader {
 public:
  virtual map<string, variant<int, string, vector<int>, vector<string>>> loadConfig (ConfigFormatType configFormat, string configLocation) = 0;
};

#endif
