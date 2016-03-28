#ifndef JPMORGANI_PERATIOCALCULATOR
#define JPMORGANI_PERATIOCALCULATOR

#include "stock.h"

template <class numericType>
struct calculatePERatio {
  numericType operator() (const Stock<numericType>& stock);
};

#endif
