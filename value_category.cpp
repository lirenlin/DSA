#include <iostream>
#include <utility>

void foo(int && i)
{
  std::cout << i << ": rvalue referece overload!\n";
}

void foo(const int & i)
{
  std::cout << i << ": lvalue referece overload!\n";
}

void foo(int i)
{
  std::cout << i << ": lvalue overload!\n";
}

int main()
{
  //prvalue could bind to both lvalue, rvalue reference, const lvalue reference
  foo(12);

  int a = 10;
  // lvalue could bind to both lvalue and lvalue reference.
  // lvalue could not bind to rvalue reference
  foo(a);

  //xvalue could bind to rvalue reference, lvalue, lvalue reference
  foo(std::move(a));
  return 0;
}

