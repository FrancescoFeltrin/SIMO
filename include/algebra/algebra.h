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
  // Modified for when you don't use the arduino...
#endif /* CPU_ARCH*/

template<unsigned int nR,unsigned int nC =1, class T =float>
class Gmatrix{
private:
  BLA::Matrix<(int)nR,(int)nC, BLA::Array<nR,nC,T> > mat; //protected to avoid bypassing the interface
  Gmatrix(BLA::Matrix<nR,  nC, BLA::Array<nR,nC,T> > m);  //protected to bypassing the interface
public:
  Gmatrix();
  Gmatrix(const Gmatrix& toCopy);
  Gmatrix& operator=(const Gmatrix& b);
  unsigned int nRow()const;
  unsigned int nCol()const;
  //Access
  T& operator()(int row,int col = 0);
  const T& operator()(int row,int col = 0)const;
  const T& cAccess(int row,int col = 0)const;
  Gmatrix& fill(const T& element);
  Gmatrix<1,nR,T> operator[](int idx)const; // A[1][2] gives a 1x1 matrix with the element in A(1,2)
  //Algebra
  Gmatrix operator+(const Gmatrix &b);
  Gmatrix operator-(const Gmatrix &b);
  Gmatrix& operator+=(const Gmatrix& m2);
  Gmatrix& operator-=(const Gmatrix& m2);

  Gmatrix operator*(const T& scalar);
  friend Gmatrix operator*(const T& scalar, const Gmatrix& M ){
    return Gmatrix(M.mat*scalar); //must be implemented here I believe...
  }
  template <unsigned int operandCols,class Tt>
  Gmatrix<nR,operandCols,T> operator*(const Gmatrix<nC,operandCols,Tt> & b)const;

  template <class Tt>  bool operator==(const Gmatrix<nR,nC,Tt>& b)const;
  bool operator!=(const Gmatrix& b)const;
  //Unary Overload
  Gmatrix operator-() const;
  //Matrix functions
  Gmatrix<nC,nR,T> t()const;
  Gmatrix          inv()const;
  T                det()const;
  /*
  friend Gmatrix Hconcat(const& Gmatrix b) const{}:
  friend Gmatrix Vconcat(const& Gmatrix b) const{}:*/
};


// ===================================================================================


template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T>::Gmatrix(BLA::Matrix<nR, nC, BLA::Array< nR,nC,T> > m):mat(m){};

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T>::Gmatrix(){};

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T>::Gmatrix(const Gmatrix& toCopy):mat(toCopy.mat){};

template<unsigned int nR,unsigned int nC, class T>
unsigned int Gmatrix<nR,nC,T>::nRow()const {
  return (unsigned int) mat.GetRowCount();
}

template<unsigned int nR,unsigned int nC, class T>
unsigned int Gmatrix<nR,nC,T>::nCol()const{
  return (unsigned int) mat.GetColCount();
}

template<unsigned int nR,unsigned int nC, class T>
T& Gmatrix<nR,nC,T>::operator()(int row,int col){  //unprotected access
  /*if ( (row>(int)nRow())||(col>(int)nCol()) ) {
    std::cout<<"Error! Out of bound"<<std::endl;  }*/
  return mat(row,col);
}

template<unsigned int nR,unsigned int nC, class T>
const T& Gmatrix<nR,nC,T>::operator()(int row,int col)const{  //unprotected access
  /*if ( (row>(int)nRow())||(col>(int)nCol()) ) {
    std::cout<<"Error! Out of bound"<<std::endl;  }*/
  return cAccess(row,col);
}

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T>& Gmatrix<nR,nC,T>::fill(const T& element){
  mat.Fill(element);
  return *this;
}

template<unsigned int nR,unsigned int nC, class T>
const T& Gmatrix<nR,nC,T>::cAccess(int row,int col) const{  //protected access
  return mat(row,col);
}

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<1,nR,T> Gmatrix<nR,nC,T>::operator[](int idx)const{
  Gmatrix<1,nR,T> singleRow;
  for (int i=0; i< (int) nR;++i)
    singleRow(0,i) = (*this).cAccess(i,idx);
  return singleRow;
}
//=====================  Algebra
template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T> Gmatrix<nR,nC,T>::operator+(const Gmatrix &b){
  return Gmatrix(mat+b.mat);
}

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T> Gmatrix<nR,nC,T>::operator-(const Gmatrix &b){
  return Gmatrix(mat-b.mat);
}

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T> Gmatrix<nR,nC,T>::operator*(const T& scalar){
  return Gmatrix(mat*scalar);
}

template<unsigned int nR,unsigned int nC, class T>
template <unsigned int operandCols,class Tt> Gmatrix<nR,operandCols,T> Gmatrix<nR,nC,T>::operator*(const Gmatrix<nC,operandCols,Tt> & b)const{
  Gmatrix<nR,operandCols,T> output;
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

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T>& Gmatrix<nR,nC,T>::operator=(const Gmatrix<nR,nC,T>& b){  //assignment operator
  mat = b.mat;
  return *this;
}

template<unsigned int nR,unsigned int nC, class T>
template<class Tt>
bool Gmatrix<nR,nC,T>::operator==(const Gmatrix<nR,nC,Tt>& b)const{
  if ( ( nRow()!=b.nRow() )|(nCol()!=b.nCol()) ) return false;
  for ( int r = 0; r<(int)nRow(); r++){
    for ( int c = 0; c<(int)nCol(); c++){
      if ( cAccess(r,c)!= b.cAccess(r,c) ) return false;
    }
  }
  return true;
}

template<unsigned int nR,unsigned int nC, class T>
bool Gmatrix<nR,nC,T>::operator!=(const Gmatrix<nR,nC,T>& b)const{
  return !(*this== b);
}

//Unary Overload
template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T> Gmatrix<nR,nC,T>::operator-() const{
  Gmatrix negative(-mat);
  return negative;
}

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T>& Gmatrix<nR,nC,T>::operator+=(const Gmatrix<nR,nC,T>& m2) {
  mat += m2.mat;
  return *this;
}

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T>& Gmatrix<nR,nC,T>::operator-=(const Gmatrix<nR,nC,T>& m2) {
  mat -= m2.mat;
  return *this;
}

//Matrix functions
template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nC,nR,T> Gmatrix<nR,nC,T>::t() const{ //transpose
  Gmatrix<nC,nR,T> output;
  for (unsigned int i=0; i<nR; ++i){
    for (unsigned int j=0; j<nC; ++j){
      output(j,i)= this->cAccess(i,j);
    }
  }
  return output;
}

template<unsigned int nR,unsigned int nC, class T>
Gmatrix<nR,nC,T> Gmatrix<nR,nC,T>::inv() const{
  return Gmatrix(this->mat.Inverse());
}

template<unsigned int nR,unsigned int nC, class T>
T Gmatrix<nR,nC,T>::det() const{
  return mat.Det();
}

template<class T>
T cast(const Gmatrix<1,1,T>& a) {
  return a.cAccess(0,0);
}

//template<class T> T operator T {
//  return cAccess(0,0);
//}

#endif
