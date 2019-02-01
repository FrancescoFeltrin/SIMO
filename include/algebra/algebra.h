#ifndef ALGEBRA_H
#define ALGEBRA_H

/* This is a wrapper template to provide a standard interface.
If you change CPU/microController architecture and want to use a different matrix library, you only
have to change it here.
NB: The desired featrues are:
  - Matrix operation WITHOUT dynamic allocation.
  - Possibly compile time size error detection.
  - Indexing start at ZERO (looking at you matlab)
*/


#ifdef ARDUINO_ARCH
#include "BasicLinearAlgebra.h"
/* Thanks to
author  = Tom Stewart <tomstewart89@hotmail.com>
name    = BasicLinearAlgebra
url     = https://github.com/tomstewart89/BasicLinearAlgebra
*/

template<unsigned int nC,unsigned int nR =1, class T = int>
class Gmatrix{
private:
  BLA::Matrix<(int)nC,(int)nR,T> mat; //protected to avoid bypassing the interface
  Gmatrix(BLA::Matrix<nC,nR,T> m):mat(m){};
public:
  Gmatrix(){};
  Gmatrix(const Gmatrix& toCopy) = default;
  unsigned int nRow()const{
    return (unsigned int) mat.GetRowCount();
  }
  unsigned int nCol()const{
    return (unsigned int) mat.GetColCount();
  }
  T& operator()(int row,int col = 0){  //unprotected access
    return &mat(row,col);
  }
  friend Gmatrix& operator=(const Gmatrix& b){  //assignment operator
    mat = b.mat();
  }
  friend bool operator==(const Gmatrix& b){
    return (mat==b.mat);
  }
  //Unary Overload
  Gmatrix& operator-() const{};
  Gmatrix& operator+=(const Gmatrix& m2) {};
  Gmatrix& operator-=(const Gmatrix& m2) {};

  //Algebra
  friend Gmatrix operator+(const Gmatrix &a,const Gmatrix &b) const{};
  friend Gmatrix operator-(const Gmatrix &a,const Gmatrix &b) const{};
  friend Gamtrix operator*(const Gmatrix &a,const Gmatrix &b) const{};

  //Matrix functions
  Gmatrix inv() const{
    return Gmatrix(this->mat.Inverse())
  };
  Gmatrix t()   const{
    return Gmatrix(~(this->mat));
  };
  friend Gmatrix Hconcat(const& Gmatrix b) const{}:
  friend Gmatrix Vconcat(const& Gmatrix b) const{}:
};
#endif /* ARDUINO_ARCH*/


#ifdef CPU_ARCH
#include "MemoryDelegate2.hpp"
#include "BasicLinearAlgebra2.h"
/* Modified for when you don't use the arduino from
name    = BasicLinearAlgebra
*/

template<unsigned int nR,unsigned int nC =1, class T =float>
class Gmatrix{
private:
  BLA::Matrix<(int)nR,(int)nC, BLA::Array<nR,nC,T> > mat; //protected to avoid bypassing the interface
  Gmatrix(BLA::Matrix<nC,nR,BLA::Array<nR,nC,T> > m):mat(m){
    //std::cout<<" private copy by internal matrix"<<std::endl;
  };
public:
  Gmatrix(){};
  Gmatrix(const Gmatrix& toCopy):mat(toCopy.mat){
    //std::cout<<" public copy constructor"<<std::endl;
  };
  unsigned int nRow()const{
    return (unsigned int) mat.GetRowCount();
  }
  unsigned int nCol()const{
    return (unsigned int) mat.GetColCount();
  }
  T& operator()(int row,int col = 0){  //unprotected access
    return mat(row,col);
  }

  const T& cAccess(int row,int col = 0) const{  //protected access
    return mat(row,col);
  }

  //Algebra
  Gmatrix operator+(const Gmatrix &b){
    return Gmatrix(mat+b.mat);
  };
  Gmatrix operator-(const Gmatrix &b){
    return Gmatrix(mat-b.mat);
  };
  Gmatrix operator*(const Gmatrix &b){
    return Gmatrix(mat*b.mat);
  };

  Gmatrix & operator=(const Gmatrix& b){  //assignment operator
    mat = b.mat;
    return *this;
  };

  bool operator==(const Gmatrix& b)const{
    if ( ( nRow()!=b.nRow() )|(nCol()!=b.nCol()) ) return false;
    for ( int r = 0; r<(int)nRow(); r++){
      for ( int c = 0; c<(int)nCol(); c++){
        if ( cAccess(r,c)!= b.cAccess(r,c) ) return false;
      }
    }
    return true;
  };

  bool operator!=(const Gmatrix& b)const{
    return !(*this== b);
  };
  //Unary Overload
  Gmatrix operator-() const{
    Gmatrix negative(-mat);
    return negative;
  };

  Gmatrix& operator+=(const Gmatrix& m2) {
    mat += m2.mat;
    return *this;
  };

  Gmatrix& operator-=(const Gmatrix& m2) {
    mat -= m2.mat;
    return *this;
  };

  //Matrix functions
  Gmatrix t()   const{ return Gmatrix(~(this->mat));};
  Gmatrix inv() const{ return Gmatrix(this->mat.Inverse());};
  /*
  friend Gmatrix Hconcat(const& Gmatrix b) const{}:
  friend Gmatrix Vconcat(const& Gmatrix b) const{}:*/
};
#endif /*CPU_ARCH*/

#endif
