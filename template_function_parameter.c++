#include <iostream>

inline int add1(int i){ return i+1; }
inline int add2(int i){ return i+2; }
using FuncPtr = int (*)(int);

class Base {
public:
    virtual void doTemplate () = 0;
};

template <FuncPtr func>
class Dummy: public Base {
public:
  int a;

  Dummy(int a):a(a) {}
  void doTemplate(){
      std::cout << "Do Template: " << func(a) << "\n";
  }
};

int main ()
{
  int choice;
  std::cout << "Enter choice: ";
  std::cin >> choice;

  Base *ptr;

  if (choice == 0) {
    ptr = new Dummy<add1>(choice);
  }
  else {
    ptr = new Dummy<add2>(choice);
  }

  ptr->doTemplate();
  delete ptr;

  return 0;
}
