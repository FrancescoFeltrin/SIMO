//Simple test to see if I understand template

//#define CATCH_CONFIG_MAIN //only in one cpp

#include "../../include/catch.hpp"
#include "../../include/units/UnitsTemplate.h"
#include <cmath>

//Set up for the whole test suite
using type1 = int;
using type2 = unsigned int;
type1 a_value = 100;
type1 b_value = 550;
type2 a_error = 40;
type2 b_error = 30;

Measure<type1,type2> a(a_value,a_error);
Measure<type1,type2> b(b_value,b_error);

TEST_CASE("Measurement constructors & basics","[basics]"){
  REQUIRE(a.value == (type1) a_value);
  REQUIRE(a.error == (type2) a_error);
  REQUIRE(b.value == (type1) b_value);
  REQUIRE(b.error == (type2) b_error);
}

TEST_CASE("Measurement arithmetic","[basics]"){
  //Measure<type1,type2> d= a+b;
  REQUIRE((a + b).value == (type1) a_value+b_value );
  REQUIRE((a + b).error == (type2) sqrt( pow(a_error,2) + pow(b_error,2) ));
  REQUIRE((a - b).value == (type1) a_value-b_value );
  REQUIRE((a - b).error == (type2) sqrt( pow(a_error,2) + pow(b_error,2) ));
  REQUIRE((a * b).value == (type1)  a_value*b_value  );
  REQUIRE((a / b).value == (type1)  a_value/b_value  );
}

TEST_CASE("Conversions and arithmetic","[basics]"){
  //Measure<type1,type2> d= a+b;
  REQUIRE((a + 4).value == (type1) a_value+4 );
  REQUIRE((a + 4).error == (type2) a_error   );
  REQUIRE((a - 4).value == (type1) a_value-4 );
  REQUIRE((a - 4).error == (type2) a_error   );
  REQUIRE((a * 4).value == (type1) a_value*4 );
  REQUIRE((a / 4).value == (type1) a_value/4 );
}

TEST_CASE("Exact powers","[basics]"){
  Measure<type1,type2> d(10,1);
  Measure<type1,type2> e = pow(d,2);
  Measure<type1,type2> f(10,5);
  Measure<type1,type2> g = pow(f,2);
  REQUIRE( e.value == (type1) 100 );
  REQUIRE( e.error == (type2) 20);
  REQUIRE( g.value == (type1) 100 );
  REQUIRE( g.error == (type2) 100);
}

TEST_CASE("Cpmparisons ","[basics]"){
  //Measure<type1,type2> d= a+b;
  Measure<type1,type2> a_min(a_value-a_error*4, a_error/10);
  Measure<type1,type2> a_max(a_value+a_error*4, a_error/10);
  Measure<type1,type2> a_approx(a_value+a_error, a_error);
  REQUIRE( (a < a_min) == false );
  REQUIRE( (a > a_max) == false );
  REQUIRE( (a > a_min) == true  );
  REQUIRE( (a < a_max) == true  );
  REQUIRE( (a == a_approx)==  true);
  REQUIRE( (a != a_min) == true );
}


// Compile and run
// $ g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -o testxxx testxxx.cpp
// $ ./testxxx  --success
