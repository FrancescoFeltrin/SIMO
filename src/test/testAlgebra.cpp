//Testing if the Matrix algebra works with the correct interface
#include "../../include/catch.hpp"
#include "../../include/minimalInterface/minInterface.h"
#include "../../include/algebra/algebra.h"
#include <cmath>

//Set up for the whole test suite

Gmatrix<3,3,float> M1;
Gmatrix<3,1,float> v1;
Gmatrix<1,3,float> r1;
Gmatrix<3,3,float> M2;


TEST_CASE("Algebra: correct sizing","[basics]"){
  REQUIRE( M1.nCol()==3);
  REQUIRE( M1.nRow()==3);
  REQUIRE( r1.nCol()==3);
  REQUIRE( r1.nRow()==1);
  REQUIRE( v1.nCol()==1);
  REQUIRE( v1.nRow()==3);

}


TEST_CASE("Algebra: matrix assignment and copy","[basics]"){
  M1(0,0) = 1.0;
  M1(1,1) = 1.0;
  M1(2,2) = 1.0;
  M1(0,1) = 0;   M1(0,2) = 0;
  M1(1,0) = 0;   M1(1,2) = 0;
  M1(2,0) = 0;   M1(2,1) = 0;
  REQUIRE( M1(0,0)==1.0);
  REQUIRE( M1(1,1)==1.0);
  REQUIRE( M1(2,2)==1.0);
  REQUIRE( M1(0,1)== 0);

  v1(0) = 1;   v1(1) = 1;   v1(2) = 1;
  r1(0,0) = 2; r1(0,1) = 2; r1(0,2) = 2;
  REQUIRE( v1(0)== 1);
  REQUIRE( v1(1)== 1);
  REQUIRE( v1(2)== 1);
  REQUIRE( r1(0,0)== 2);
  REQUIRE( r1(0,1)== 2);
  REQUIRE( r1(0,2)== 2);

  M2 = M1;
  REQUIRE( M2(0,0)== 1);
  REQUIRE( M2(1,1)== 1);
  REQUIRE( M2(2,2)== 1);
  REQUIRE( M2(0,1)== 0);

  Gmatrix<3,3,float> Mcc(M1); //copy constructor
  REQUIRE( Mcc(0,0)== 1);
  REQUIRE( Mcc(1,1)== 1);
  REQUIRE( Mcc(2,2)== 1);
  REQUIRE( Mcc(0,1)== 0);
}

Gmatrix<3,3,float> M3; //copy constructor

TEST_CASE("Algebra: addtion and subtraction ","[basics]"){
  M3 = M2+M1;
  REQUIRE( M3(0,0) == 2 );
  REQUIRE( M3(1,1) == 2 );
  REQUIRE( M3(2,2) == 2 );

  Gmatrix<3,3,float> Md;
  Md = M3-M2;
  REQUIRE( Md(0,0) == 1 );
  REQUIRE( Md(1,1) == 1 );
  REQUIRE( Md(2,2) == 1 );

  Gmatrix<3,3,float> Mp;
  Mp = M1*M2; //all identity matrices
  REQUIRE( Mp == M1 );
}

TEST_CASE("Algebra: operation between vectors and matrices ","[basics]"){
  REQUIRE(1==1);
}

TEST_CASE("Algebra: tranposition ","[basics]"){
  Gmatrix<3,3,float> MT;
  MT(0,0)= 1.0;  MT(0,1)= 0;   MT(0,2)= 0;
  MT(1,0)= 1.0;  MT(1,1)= 0;   MT(1,2)= 0;
  MT(2,0)= 1.0;  MT(2,1)= 0;   MT(2,2)= 0;

  Gmatrix<3,3,float> M;
  M(0,0)= 1; M(0,1)= 1; M(0,2)= 1;
  M(1,0)= 0; M(1,1)= 0; M(1,2)= 0;
  M(2,0)= 0; M(2,1)= 0; M(2,2)= 0;
  REQUIRE( MT.t() == M );
  REQUIRE( M.t()  == MT);
}

TEST_CASE("Algebra: square matrix inversion ","[basics]"){
  REQUIRE( M1.inv() == M1);
}

//left to test, unary -, +=, -=, !=, inv, horizontal and vertical concatenation,
