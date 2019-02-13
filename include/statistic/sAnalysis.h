/* Statistical Analysis converts an array of data (assumed to rapresent the same value)
to a more precise value stored in a dataL (L=long).
C style array used to avoid dyanamic allocation.
 To do:
  -Include overflow protection
*/
#ifndef SANALYSIS_H
#define SANALYSIS_H

#include "../units/units.h"


dataL sAnalysis(const data array[],unsigned int aSize);

#endif
