#ifndef ALGEBRA_H
#define ALGEBRA_H

/* This is a wrapper template to provide a standard interface.
If you change CPU/microController architecture and want to use a different matrix library, you only
have to change it here.
NB: The desired featrues are:
  - Matrix operation WITHOUT dynamic allocation.
  - Possibly compile time size error detection.
  - Indexing start at ZERO (looking at you matlab)
To fix:
  - Separate implementation from declaration (in this file)
  - matrix multiplication; is it correct?
*/



#ifdef ARDUINO_ARCH
#include "MemoryDelegate.hpp"
#include "BasicLinearAlgebra.h"
/* Thanks to
author  = Tom Stewart <tomstewart89@hotmail.com>
name    = BasicLinearAlgebra
url     = https://github.com/tomstewart89/BasicLinearAlgebra
*/
#endif /* ARDUINO_ARCH*/


#ifdef CPU_ARCH
#include "MemoryDelegate2.hpp"
#include "BasicLinearAlgebra2.h"
/* Modified for when you don't use the arduino from
name    = BasicLinearAlgebra
*/
#endif /* CPU_ARCH*/

template<unsigned int nR,unsigned int nC =1, class T =float>
class Gmatrix{
private:
  BLA::Matrix<(int)nR,(int)nC, BLA::Array<nR,nC,T> > mat; //protected to avoid bypassing the interface
  Gmatrix(BLA::Matrix<nC,nR,BLA::Array<nR,nC,T> > m):mat(m){};
public:
  Gmatrix(){};

  Gmatrix(const Gmatrix& toCopy):mat(toCopy.mat){};
  unsigned int nRow()const {
    return (unsigned int) mat.GetRowCount();
  }
  //Access
  unsigned int nCol()const{
    return (unsigned int) mat.GetColCount();
  }

  T& operator()(int row,int col = 0){  //unprotected access
    /*if ( (row>(int)nRow())||(col>(int)nCol()) ) {
      std::cout<<"Error! Out of bound"<<std::endl;  }*/
    return mat(row,col);
  }
  Gmatrix& fill(const T& element){
    mat.Fill(element);
    return *this;
  }
//  Gmatrix operator[](int idx){}

  const T& cAccess(int row,int col = 0) const{  //protected access
    return mat(row,col);
  }

  //Algebra
  Gmatrix operator+(const Gmatrix &b){
    return Gmatrix(mat+b.mat);
  }

  Gmatrix operator-(const Gmatrix &b){
    return Gmatrix(mat-b.mat);
  }

  Gmatrix operator*(const Gmatrix &b){
      return Gmatrix(mat*b.mat);
  }

  Gmatrix operator*(const T& scalar){
    return Gmatrix(mat*scalar);
  }

  friend Gmatrix operator*(const T& scalar, const Gmatrix& M ){
    return Gmatrix(M.mat*scalar);
  }

  template <unsigned int operandCols,class Tt> Gmatrix<nR,operandCols,T> operator*(const Gmatrix<nC,operandCols,Tt> & b) const{
    Gmatrix<nR,operandCols,T> output; //I could do it in loops...
    output.fill(0);
    for (unsigned int oR = 0; oR<nR;oR++){
      for (unsigned int oC = 0; oC<operandCols;oC++){
        for (unsigned int i = 0; i<nC; ++i){
            output(oR,oC) += (*this).cAccess(oR,i)*b.cAccess(i,oC);
          }
        }
    }
    return output;
  }

  Gmatrix & operator=(const Gmatrix& b){  //assignment operator
    mat = b.mat;
    return *this;
  }

  bool operator==(const Gmatrix& b)const{
    if ( ( nRow()!=b.nRow() )|(nCol()!=b.nCol()) ) return false;
    for ( int r = 0; r<(int)nRow(); r++){
      for ( int c = 0; c<(int)nCol(); c++){
        if ( cAccess(r,c)!= b.cAccess(r,c) ) return false;
      }
    }
    return true;
  }

  bool operator!=(const Gmatrix& b)const{
    return !(*this== b);
  }

  //Unary Overload
  Gmatrix operator-() const{
    Gmatrix negative(-mat);
    return negative;
  }

  Gmatrix& operator+=(const Gmatrix& m2) {
    mat += m2.mat;
    return *this;
  }

  Gmatrix& operator-=(const Gmatrix& m2) {
    mat -= m2.mat;
    return *this;
  }

  //Matrix functions
  Gmatrix<nC,nR,T> t() const{ //transpose
    Gmatrix<nC,nR,T> output;
    for (unsigned int i=0; i<nR; ++i){
      for (unsigned int j=0; j<nC; ++j){
        output(j,i)= this->cAccess(i,j);
      }
    }
    return output;
  }

  Gmatrix inv() const{ return Gmatrix(this->mat.Inverse());};
  T det() const{ return mat.Det();}
  /*
  friend Gmatrix Hconcat(const& Gmatrix b) const{}:
  friend Gmatrix Vconcat(const& Gmatrix b) const{}:*/
};


#endif
