#ifndef UNITS_H
#define UNITS_H
#include "UnitsTemplate.h"

// This is a simple interface to the Measure class, which handles error propagation.
// Measure is a template so that you can change the rapresentation (if you need more precision).
// Also, it avoids repetitions.

using data = Measure<int,unsigned int>;
/* This is for digital data, with fast arithmetic. max value ~ +32000 min -32000
   Use them with care.
*/
using dataL = Measure<float,float>;

#endif
