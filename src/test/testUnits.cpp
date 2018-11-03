//Simple test to see if I understand template

//#define CATCH_CONFIG_MAIN //only in one cpp

//#include "../../include/catch.hpp"
#include "catch.hpp"
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

TEST_CASE("Measurement constructors & basics","[assign]"){
  REQUIRE(a.value == (type1) a_value);
  REQUIRE(a.error == (type2) a_error);
  REQUIRE(b.value == (type1) b_value);
  REQUIRE(b.error == (type2) b_error);
}

TEST_CASE("Measurement arithmetic","[arithmetic]"){
  //Measure<type1,type2> d= a+b;
  REQUIRE((a + b).value == (type1) a_value+b_value );
  REQUIRE((a + b).error == (type2) sqrt( pow(a_error,2) + pow(b_error,2) ));
  REQUIRE((a - b).value == (type1) a_value-b_value );
  REQUIRE((a - b).error == (type2) sqrt( pow(a_error,2) + pow(b_error,2) ));
  REQUIRE((a * b).value == (type1)  a_value*b_value  );
  REQUIRE((a / b).value == (type1)  a_value/b_value  );
}

TEST_CASE("Conversions and arithmetic","[arithmetic]"){
  //Measure<type1,type2> d= a+b;
  REQUIRE((a + 4).value == (type1) a_value+4 );
  REQUIRE((a + 4).error == (type2) a_error   );
  REQUIRE((a - 4).value == (type1) a_value-4 );
  REQUIRE((a - 4).error == (type2) a_error   );
  REQUIRE((a * 4).value == (type1) a_value*4 );
  REQUIRE((a / 4).value == (type1) a_value/4 );
}

TEST_CASE("Exact powers","[arithmetic]"){
  Measure<type1,type2> d = pow(a,2);
  REQUIRE( d.value == (type1) pow(a_value,2) );
  REQUIRE( d.error == (type2) 2*(a.error / fabs( a.value) )*fabs(a_value) );
}

TEST_CASE("Cpmparisons ","[arithmetic]"){
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
