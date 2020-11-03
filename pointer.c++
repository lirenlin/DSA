#include <iostream>

int sum (int *a, int *b)
{
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  int c = *a + *b;
  return c;
}

int main()
{
  int x = 10;
  int y = 11;
  int *a = &x;
  int *b = &y;
  std::cout << &a << std::endl;
  std::cout << &b << std::endl;
  std::cout << sum (a, b) << std::endl;


  return 0;
}
