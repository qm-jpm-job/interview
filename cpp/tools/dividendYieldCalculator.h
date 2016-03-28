#ifndef JPMORGANI_DIVIDENDYIELDCALCULATOR
#define JPMORGANI_DIVIDENDYIELDCALCULATOR

#include "commonStock.h"
#include "preferredStock.h"

template <class stockType, class numericType>
struct calculateDividendYield {
  numericType operator() (const stockType& stock);
};

template <class numericType>
struct calculateDividendYield <CommonStock<numericType>, numericType> {
  numericType operator() (const CommonStock<numericType>& stock); 
};

template <class numericType>
struct calculateDividendYield <PreferredStock<numericType>, numericType> {
  numericType operator() (const PreferredStock<numericType>& stock); 
};

#endif
