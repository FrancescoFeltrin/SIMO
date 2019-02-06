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
  //using c array syntax
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

TEST_CASE("Algebra: scalar multiplication","[basics]"){
  Gmatrix<3,3,float> M_id;
  M_id(0,0)= 1.0;  M_id(0,1)= 0;   M_id(0,2)= 0;
  M_id(1,0)= 0;    M_id(1,1)= 1.0; M_id(1,2)= 0;
  M_id(2,0)= 0;    M_id(2,1)= 0;   M_id(2,2)= 1.0;
  REQUIRE( (M_id*3)(0,0)==3);
  REQUIRE( (2*M_id)(1,1)==2);
  REQUIRE( 3*M_id-2*M_id==M_id);
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
  Gmatrix<3,3,float> M;
  M(0,0)= 1.0;  M(0,1)= 0;   M(0,2)= 0;
  M(1,0)= 0;    M(1,1)= 2.0; M(1,2)= 0;
  M(2,0)= 0;    M(2,1)= 0;   M(2,2)= 3.0;

  Gmatrix<3,1,float> v;
  v(0)  = 2;  v(1)  = 2;  v(2) = 2;
  Gmatrix<1,3,float> c;
  c(0,0) = 1; c(0,1) = 1; c(0,2) = 1;

  REQUIRE( (M*v)(0) == 2);
  REQUIRE( (M*v)(1) == 4);
  REQUIRE( (M*v)(2) == 6);

  REQUIRE( (c*M)(0,0) == 1);
  REQUIRE( (c*M)(0,1) == 2);
  REQUIRE( (c*M)(0,2) == 3);

  REQUIRE( (M*c.t())(0) == 1);
  REQUIRE( (M*c.t())(1) == 2);
  REQUIRE( (M*c.t())(2) == 3);

  Gmatrix<1,3,float> C;
  C= c+c;
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
  REQUIRE( M1.det()!= 0);
  REQUIRE( M1.inv() == M1);
  REQUIRE( ((2*M1).inv())(0,0) == 0.5);

  Gmatrix<3,3,float> M_a;
  Gmatrix<3,3,float> M_b;

  M_a(0,0)= 1;  M_a(0,1)= 0;   M_a(0,2)= 8;
  M_a(1,0)= 0;  M_a(1,1)= 4;   M_a(1,2)= 0;
  M_a(2,0)= 4;  M_a(2,1)= 0;   M_a(2,2)= 2;

  M_b(0,0)= -1.0/15;  M_b(0,1)= 0;   M_b(0,2)= 4.0/15;
  M_b(1,0)=   0;      M_b(1,1)= 1.0/4;   M_b(1,2)= 0;
  M_b(2,0)=  2.0/15;  M_b(2,1)= 0;  M_b(2,2)= -1.0/30;
  REQUIRE( M_a != M_b);

  //here there might be numberical errors to be fixed!
  REQUIRE( (M_a*M_b)(0,0) == 1.0);
  REQUIRE( (M_a*M_b)(0,1) == 0.0);
  REQUIRE( (M_a*M_b)(0,2) == 0.0);

  REQUIRE( (M_a*M_b)(1,0) == 0.0);
  REQUIRE( (M_a*M_b)(1,1) == 1.0);
  REQUIRE( (M_a*M_b)(1,2) == 0.0);

  REQUIRE( (M_a*M_b)(2,0) == 0.0);
  REQUIRE( (M_a*M_b)(2,1) == 0.0);
  REQUIRE( (M_a*M_b)(2,2) == 1.0);

  REQUIRE( (M_a*M_b).det() == 1.0);
  REQUIRE( M_a.inv()== M_b); //ideally...
//  REQUIRE( M_b.inv()== M_a); //ideally...
}


//left to test, unary -, +=, -=, horizontal and vertical concatenation,
