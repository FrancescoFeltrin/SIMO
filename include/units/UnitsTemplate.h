//Test Template for the unit class
#ifndef UNITSTEMPLATE_H
#define UNITSTEMPLATE_H
#include <cmath>
#include <iostream>

/*It ROUGHLY handles error propagation, with no dimensional check (yet):
  -Assumes the errors are UNCORRELATED GAUSSIAN prob distribution,
  -Assumes you do operations that make sense [unit wise]
  -Comparison like >, < are implemented at 3 sigma -> a<b == true IF you are sure at 99.6%
  -Comparison like (a == b )  = true IF the probability that they are equal is at least 99.6%
Implemenation details:
  -The type you see on the outside are alias of templates. Alias are used to simplify notation,
  templates are used to avoid repetition and allow different lenght data (float vs int), which
  is something you need in microprocessors (like arduino).
  -In oredr to behave algebrically as expected (both with other measurement and
  with exact numbers) external overload of aritmetic is implemented with friend.
  In this way you should be able to to  a+b, a+5, 5+a ,a+5.0 as long as you have a
  constructor able to convert from TYPE of 5.0 to measure.
To fix:
  - I would like the friend implemenation to be separated.
  - Possibly in a cpp, but with templates It might not be possible
  - If not, at left outside of the class definition...
  - To fix the pow function to real exponent and negative values as base
  - Power function fails some tests
To improve :
  - I could add a scale factor <k> in the template definition to store the "error"
  value in a different unit compared to the value. (One would expect the error to be
  smaller than the value itself). This way you can get away with int operations without
  loosing too much accuracy.
*/



template <class V,class E>
class Measure{
  private:
    V relError()const { return ((V) error) / value;};
  public:
    V value;
    E error;
    Measure(){}; //to allocate
    Measure(const V& mean ,const E& sigma ): value(mean),error(sigma){};
    //As long as you have constructors for it, arithmetic should work
    Measure(const int& mean): value((V) mean),error(0){};
    Measure(const unsigned int& mean): value((V) mean),error(0){};
    Measure(const float & mean): value((V) mean),error(0){};
    Measure(const double & mean): value((V) mean),error(0){};
    Measure(const Measure & ) = default;
    Measure& operator = (const Measure & assigned){
      this->value = assigned.value;
      this->error = assigned.error;
      return *this;
    };
    //unary Overload
    Measure operator-() const;

    //Overload of arithmetic with similar measures
    friend Measure operator+(const Measure & a, const Measure & b) {
        E nError = sqrt( pow(a.error,2) + pow(b.error,2) );
        return Measure(a.value+b.value,nError);
    }
    friend Measure operator-(const Measure & a, const Measure & b) {
        E nError = sqrt( pow(a.error,2) + pow(b.error,2) );
        return Measure(a.value-b.value,nError);
    }
    friend Measure operator*(const Measure & a, const Measure & b) {
      V res = a.value * b.value;
      E relError = sqrt(pow(a.relError(),2)+pow(b.relError(),2));
      E absError = fabs(res*relError); //need to force floating point abs!
      return Measure(res,absError);
    }
    friend Measure operator/(const Measure & a, const Measure & b) {
      V res = a.value / b.value;
      E relError = sqrt(pow(a.relError(),2)+pow(b.relError(),2));
      E absError = fabs(res*relError);//need to force floating point abs!
      return Measure(res,absError);
    }
    //Implicit Conversions are a no-no as they cause ambiguity in cases such (5+a)

    //Comparisons operators
    bool lessThanAtSigma(const Measure& target,float Sigma=3.0) const;

    friend bool operator<(const Measure &a, const Measure &b){//This way conversion is enforced
      return a.lessThanAtSigma(b);
     };
    friend bool operator>(const Measure &a, const Measure &b){
     return b.lessThanAtSigma(a);
    };
    friend bool operator==(const Measure &a, const Measure &b){
     return ((!b.lessThanAtSigma(a)) && (!a.lessThanAtSigma(b)));
    };
    friend bool operator!=(const Measure &a, const Measure &b){
     return ((b.lessThanAtSigma(a)) || (a.lessThanAtSigma(b)));
    };
    friend bool operator<=(const Measure &a, const Measure &b){
      return ( (a<b) || (a == b));
     };
    friend bool operator>=(const Measure &a, const Measure &b){
      return ( (a>b) || (a == b));
    };
};

template <class V,class E>
Measure<V,E> Measure<V,E>::operator-() const{
  return Measure<V,E>(-value,error);
}

template <class V,class E>
bool Measure<V,E>::lessThanAtSigma(const Measure& target, float Sigma) const{
    Measure<V,E> Delta = target-(*this);
    if ( (Delta.value > 0) && (fabs(Delta.value) > Sigma*(Delta.error)) )
      return true;
    else
      return false;
}

//--------- External Overloading, which don't care about order
template<class V,class E>
std::ostream& operator<<(std::ostream& os,const Measure<V,E>& m){
  if ( m.error > 0)
    return os << m.value << " +- "<< m.error;
  else
    return os << m.value;
}
/*template <class V,class E>
Measure<V,E> operator+(const Measure<V,E> & a, const Measure<V,E> & b){
  // For some reason it does not work...
}*/

//-------- Related functions
template<class V, class E>
Measure<V,E> pow( Measure<V,E> m ,int n){
  V value    = pow(m.value,n);
  E relError = abs(n)* (m.error / fabs( m.value) );
  E absError = relError * fabs(value);
  return Measure<V,E> (value,absError);
}

template<class V, class E>
Measure<V,E> pow( Measure<V,E> m ,double n){
  V value    = pow( fabs(m.value) , n);
  E relError = abs(n)* (m.error / fabs( m.value) );
  E absError = relError * (value);
  return Measure<V,E>(value,absError);
}

template<class V, class E>
Measure<V,E> sqrt( Measure<V,E> m){
  return pow(m,0.5);
}

#endif
