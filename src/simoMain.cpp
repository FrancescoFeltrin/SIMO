//Temporary main for testing on a PC. TO deploy on the arduino, supply your own
// main and #include"SIMO.h"
#include<iostream>

using namespace std;

string testFun(string input){
  string a= "some Name "+input;
  return a;
};

int main(){
  cout<<"SIMO main, which is not doing anything at the moment. "<< endl;
  string test= "string 1";
  string& b = test;
  cout << test<<endl;
  cout << testFun(b)<<endl;
}
