#ifndef JPMORGANI_LOADER
#define JPMORGANI_LOADER

#include <string>
#include <vector>

using std::string;
using std::vector;

class LibraryLoader {
 private:
  vector<void*> openLibraries;
  
 public:
  ~LibraryLoader();
  
  void* GetInstance(string libraryFilePath, string instantiatorFunctionName);
};

#endif
