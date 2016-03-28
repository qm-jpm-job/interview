#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "iniConfigReader.h"

#include <iostream>

using boost::property_tree::ptree;
using boost::property_tree::ini_parser::read_ini;

using std::pair;

void SplitString(const string& s, char c, vector<string>& v) {
  string::size_type i = 0;
  string::size_type j = s.find(c);

  while (j != string::npos) {
    v.push_back(s.substr(i, j-i));
    i = ++j;
    j = s.find(c, j);

    if (j == string::npos)
      v.push_back(s.substr(i, s.length()));
  }
}

variant<int, string, vector<int>, vector<string>> TransformConfigEntry (string configEntry) {
  variant<int, string, vector<int>, vector<string>> retVal;
  
  // Handle case with array
  if (configEntry.find(",") != string::npos) {
    vector<string> configEntries;
    SplitString(configEntry, ',', configEntries);

    try {
      vector<int> integerList;
      
      for (auto entriesIterator = configEntries.begin(); entriesIterator != configEntries.end(); entriesIterator++) {
        string curValue = *entriesIterator;

        if (curValue.length() > 0) {
          int iValue = boost::lexical_cast<int>(curValue);
          integerList.push_back(iValue);
        }        
      }

      retVal = integerList;
    } catch (...) {
      // We already have all entries as strings, so can just return
      retVal = configEntries;
    }
  } 

  // Handle case with single
  try {
    int i = boost::lexical_cast<int>(configEntry);
    retVal = i;
  } catch(...) {
    retVal = configEntry;
  }

  return retVal;
}

map<string, variant<int, string, vector<int>, vector<string>>> IniConfigReader::loadConfig (ConfigFormatType configFormat, string configLocation) { 
  map<string, variant<int, string, vector<int>, vector<string>>> configValues;

  // TODO : Boost will automatically handle any formats, though a handler should be created for possible nested types
  ptree properties;
  read_ini(configLocation, properties);

  for (auto propertyIterator = properties.begin(); propertyIterator != properties.end(); propertyIterator++) {
    string configEntry(propertyIterator->first);
    string entryValue(propertyIterator->second.get_value<string>());

    variant<int, string, vector<int>, vector<string>> variantValue = TransformConfigEntry(entryValue);
    
    configValues.insert(pair<string, variant<int, string, vector<int>, vector<string>>>(configEntry, variantValue));
  }

  return configValues;
}




