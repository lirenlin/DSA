#include <iostream>
using namespace std;

template <unsigned n>
struct Factorial
{
  enum {value = n * Factorial<n-1>::value};
};

template <>
struct Factorial<0>
{
  enum {value = 1};
};

int main ()
{
  cout << Factorial<5>::value << endl;
}
