#ifndef JPMORGANI_INICONFIGREADER
#define JPMORGANI_INICONFIGREADER

#include "IconfigReader.h"

class IniConfigReader : public IConfigReader {
 public:
  map<string, variant<int, string, vector<int>, vector<string>>> loadConfig (ConfigFormatType configFormat, string configLocation);
  
};
#endif
