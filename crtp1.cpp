//https://eli.thegreenplace.net/2011/05/17/the-curiously-recurring-template-pattern-in-c

#include <iostream>
using namespace std;

template <typename Child>
struct Base
{
  void interface()
  {
    static_cast<Child*>(this)->base1 ();
    static_cast<Child*>(this)->base2 ();
  }

  void base1 ()
  {
    cout << "base1\n";

  }

  void base2 ()
  {
    cout << "base2\n";

  }
};

struct Derived : Base<Derived>
{
  void base1 ()
  {
    cout << "Derived1\n";
  }
};

struct Base1
{
  void interface()
  {
    base1 ();
    base2 ();
  }

  void base1 ()
  {
    cout << "base1\n";

  }

  void base2 ()
  {
    cout << "base2\n";

  }
};

struct Derived1 : Base1
{
  void base1 ()
  {
    cout << "Derived1\n";
  }
};

int main()
{
  Derived d;
  d.interface();  // Prints "Derived1 base2"

  Derived1 d1;
  d1.interface();  // Prints "base1 base2"
}
