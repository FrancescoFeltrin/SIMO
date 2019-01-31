//Test for the record memory

//#define CATCH_CONFIG_MAIN //only in one cpp

#include "../../include/catch.hpp"
#include "../../include/cyclicMemory/cyclicMemory.h"
#include <iostream>

//Set up for the whole test suite
Record<int,3> intMemo,emptyM;

TEST_CASE("Cyclic Memory push","[basics]"){
  intMemo.push(1);
  REQUIRE(intMemo.read(0) == 1);
  intMemo.push(2);
  REQUIRE(intMemo.read(0) == 2);
  REQUIRE(intMemo.read(-1) == 1);
  intMemo.push(3);
  REQUIRE(intMemo[ 0] == 3);
  REQUIRE(intMemo.read(-1) == 2);
  REQUIRE(intMemo.read(-2) == 1);
  intMemo.push(4);
  REQUIRE(intMemo.read(0) == 4);
  REQUIRE(intMemo[-1] == 3);
  REQUIRE(intMemo.read(-2) == 2);
}

TEST_CASE("Check overflow and underlow behaviour","[basics]"){
  intMemo.push(3);
  intMemo.push(2);
  intMemo.push(1);
  REQUIRE(intMemo[1] == 1 ); //Over and underflow
  REQUIRE(intMemo[-4] == 3 );
}

TEST_CASE("Check container features ","[basics]"){
  REQUIRE(intMemo.size()==3);
  REQUIRE(emptyM.size() ==0);
  REQUIRE(emptyM.empty() == true ); //underflow
  REQUIRE(intMemo.empty() == false );
}

TEST_CASE("Check transitory underflow haviour","[basics]"){
  //Transitory means that you have not yet filled the buffer, but you still try to
  //read an empty location.
  emptyM.push(1);
  emptyM.push(2); //postion -3 is empty
  REQUIRE(emptyM[-3] == 1 ); //underflow
  REQUIRE(emptyM[-4] == 1 );
}
