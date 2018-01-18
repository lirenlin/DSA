/*
    Initialize one object from another of the same type.
    Copy an object to pass it as an argument to a function.
    Copy an object to return it from a function.
*/


#include <iostream>
using namespace std;

class baseA
{
public:
  baseA (): data (0)  { cout << "default baseA ctor" << endl;}
  baseA (const baseA &other): data (other.data) { cout << "baseA copy ctor with arg" << endl;}
  ~baseA () { cout << "baseA dtor" << endl;}

private:
  int data;
};

baseA foo (baseA other) { return other;}

int main ()
{
  // ctor baseA, ctor baseB, ctor derived
  // dtor derived, dtor baseB, dtor baseA
  baseA D1;
  cout << "##################" << endl;
  baseA res = foo (D1); // for res, is copy elision? return value optimisation
  cout << "##################" << endl;
  baseA D2 (res);
  cout << "##################" << endl;
  baseA D3 (foo (D1));
}
