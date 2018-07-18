//https://arne-mertz.de/2015/08/new-c-features-default-initializers-for-member-variables/
//https://stackoverflow.com/questions/11594846/default-member-values-best-practice
//-std=c++11

#include <iostream>
using namespace std;

template <int NUM>
class Dummy {
public:
  const int val = NUM;
  int x = 4;
  string str {"hello world!"};

  Dummy (int val, int x): val(val), x(5) {}; //Okay, will overwrite val and x
  Dummy (int x): x(5) {}; // will overwrite x
};

int main ()
{
  Dummy<1> dummy {2};
  cout << dummy.val << endl;
  cout << dummy.x << endl;
  cout << dummy.str << endl;
}
