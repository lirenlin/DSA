#include <iostream>
using namespace std;
/*
1. Construction always starts from the base class.
If there are multiple base classes then, it starts from the left most base.
(side note: If there is a virtual inheritance then it's given higher preference).
2. Then it comes the turn for member fields. They are initialized in the order
they are declared
3. At the last the class itself is constructed

The order of destructor is exactly reverse

 In fact, you can't call a constructor. Constructors are not
 callable by the user. Only compiler can call constructors.

 What you can do is to specify initializers.
 In this case (constructor initializer list) you are specifying initializers
 for subobjects of some larger object. The order in which you specify these
 initializers does not matter: the compiler will call the constructors in a
 very specific order defined by the language specification, regardless of the
 order in which you specify the initializers. The base class constructors are
 always called first (in the order in which the base classes are listed in
 class definition), then the constructors of member subobjects are called
 (again, in the order in which these members are listed in the class definition).

https://stackoverflow.com/questions/6247595/order-of-calling-base-class-constructor-from-derived-class-initialization-list
*/

class baseA
{
public:
  baseA (): data (0)  { cout << "default baseA ctor" << endl;}
  baseA (int a): data (a) { cout << "baseA ctor with arg" << endl;}
  ~baseA () { cout << "baseA dtor" << endl;}

private:
  int data;
};

class baseB
{
public:
  baseB (): data (0)  { cout << "default baseB ctor" << endl;}
  baseB (int a): data (a) { cout << "baseB ctor with arg" << endl;}
  ~baseB () { cout << "baseB dtor" << endl;}

private:
  int data;
};

class baseC
{
public:
  baseC (): data (0)  { cout << "default baseC ctor" << endl;}
  baseC (int a): data (a) { cout << "baseC ctor with arg" << endl;}
  ~baseC () { cout << "baseC dtor" << endl;}

private:
  int data;
};


class derived: baseA, baseB
{
public:
  derived () { cout << "derived ctor" << endl;}
  derived (int a): tmp (a), baseB (a) { cout << "derived ctor" << endl;}
  derived (int a, int b): baseB (a), baseA (b)
  { cout << "derived ctor" << endl;}

  ~derived () { cout << "derived dtor" << endl;}
private:
  baseC tmp;
};

int main ()
{
  // ctor baseA, ctor baseB, ctor derived
  // dtor derived, dtor baseB, dtor baseA
  derived *D1 = new derived ();
  delete D1;
  cout << "##################" << endl;

  derived *D2 = new derived (10);
  delete D2;
  cout << "##################" << endl;

  derived *D3 = new derived (10, 5);
  delete D3;
}
