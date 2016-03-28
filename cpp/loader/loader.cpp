#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

#include <exception>

#include "loader.h"

using std::runtime_error;

typedef void* (*initFunction) ();

void* LibraryLoader::GetInstance(string libraryFilePath, string instantiatorFunctionName) {
  void* libraryFile = dlopen(libraryFilePath.c_str(), RTLD_NOW);
  if (libraryFile == NULL) {
    throw runtime_error(string(dlerror()));
  }
      
  initFunction retTypeGenerator = (initFunction)dlsym(libraryFile, instantiatorFunctionName.c_str());

  const char* findFunctionError = dlerror();
  if (findFunctionError) {
    dlclose(libraryFile);
    throw runtime_error(string("An error occured trying to load the function from the library"));
  }
  
  void* retVal = retTypeGenerator();

  openLibraries.push_back(libraryFile);
  
  return retVal;
}

LibraryLoader::~LibraryLoader() {
  for (auto openLibsIterator = openLibraries.begin(); openLibsIterator != openLibraries.end(); openLibsIterator++) {
      dlclose(*openLibsIterator);
  }
}
