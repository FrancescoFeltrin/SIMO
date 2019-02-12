#ifndef RSTACK_H
#define RSTACK_H
/*  Read only Stack is a stack of finite depth (n), where you can not "pop".
    It models a time series which can be accessed by relative index
    (most recent data-> idx = 0, the previous one-> idx =-1, 2 time step ago idx =-2 etc).
    Features:
        -Insert and read are in constant time.
        -Data are protected and can not modified once they are added.
        -If idx is out of bound (too much in the past or in the future)
         best approximation is provided (idx < -N => idx = -N)
        -Transitory behaviour. If only 2 timesteps have been recorded and the stack is
        asked for data regarding more than 2 timesteps ago, the answer will be best approximation,
        meaning data from 2 timesteps ago.
        -Container friendly features such as empty() and size();

*/

template<class T,int n=2>
class RStack{
private:
  T buffer[n];
  unsigned int start;
  unsigned int sizeInt;
public:
  RStack();
  void push(const T& toInsert );
  const T& read(int idx) const;
  const T& operator[](int idx) const;
  unsigned int size();
  bool empty();
};

template<class T,int n>
RStack<T,n>::RStack():start(0),sizeInt(0){};

template<class T,int n>
void RStack<T,n>::push(const T& toInsert ){
         start = (start + 1) % n;
         if (sizeInt<n) ++sizeInt;
         buffer[start] = toInsert;
  }

template<class T,int n>
const T& RStack<T,n>::read(int idx) const{
  if (idx > 0) idx = 0;
  int maxHistory = -std::min((int)sizeInt,n)+1;
  if (idx < maxHistory) idx = maxHistory;
  idx = (start+idx+n) % n;
  return buffer[idx];
}

template<class T,int n>
const T& RStack<T,n>::operator[](int idx) const{
  return read(idx);
}

template<class T,int n>
unsigned int RStack<T,n>::size(){
  return sizeInt;
}

template<class T,int n>
bool RStack<T,n>::empty(){
  if (sizeInt==0) return true;
  else return false;
}

#endif
