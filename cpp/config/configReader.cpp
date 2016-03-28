#include <exception>

#include <boost/variant/get.hpp>
#include <boost/variant/apply_visitor.hpp>

#include "configReader.h"
#include "iniConfigReader.h"

using std::pair;
using std::runtime_error;

ConfigurationReader::ConfigurationReader() {
  // Initialize available configuration readers
  configReaders.insert(pair<ConfigFileType, IConfigReader*>(CF_FILE, new IniConfigReader()));
}

void ConfigurationReader::loadConfig() {
}

void ConfigurationReader::loadConfig(const tuple<ConfigFileType, ConfigFormatType, string>& config) {
  auto configReaderIterator = configReaders.find(config.get<0>());
  if (configReaderIterator == configReaders.end()) {
    throw runtime_error("No configuration reader for the particular file type is available");
  }

  configEntries = configReaders[config.get<0>()]->loadConfig(config.get<1>(), config.get<2>());
}

void ConfigurationReader::checkEntryExists(const string & configEntry) {
  auto configEntriesMapIterator = configEntries.find(configEntry);
  if (configEntriesMapIterator == configEntries.end()) {
    throw runtime_error("The requested configuration entry was not found in the configuration file");
  }
}

template <typename EntryType> EntryType ConfigurationReader::getValue(const string & configEntry) {
  checkEntryExists(configEntry);

  return boost::get<EntryType>(configEntries[configEntry]);
}

template int ConfigurationReader::getValue(const string & configEntry);
template string ConfigurationReader::getValue(const string & configEntry);
template vector<int> ConfigurationReader::getValue(const string & configEntry);
template vector<string> ConfigurationReader::getValue(const string & configEntry);
