#ifndef JPMORGANI_ALLSHAREINDEXCALCULATOR
#define JPMORGANI_ALLSHAREINDEXCALCULATOR

#include <vector>

using std::vector;

template <class numericType>
struct calculateGBCEAllShareIndex {
  numericType operator() (const vector<numericType>& prices);
};

#endif
