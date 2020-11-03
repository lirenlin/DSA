#include <iostream>

inline int add1(int i){ return i+1; }
inline int add2(int i){ return i+2; }
using FuncPtr = int (*)(int);

template <typename T>
class Base {
public:
  void doTemplate () {
      static_cast<T *>(this)->doTemplate();
  }
};

template <FuncPtr func>
class Dummy: public Base<Dummy> {
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

  if (choice == 0) {
      auto ptr = new Dummy<add1>(choice);
      ptr->doTemplate();
      delete ptr;
  }
  else {
      auto ptr = new Dummy<add2>(choice);
      ptr->doTemplate();
      delete ptr;
  }


  return 0;
}

