/*
1, For initialization of non-static const data members
2, For initialization of reference members
3, For initialization of member objects which do not have default constructor
   assignment operator
4, For initialization of base class members
5, When constructor’s parameter name is same as data member
6, For Performance reasons,
 */


#include <iostream>
class A
{
public:
  // must use initializer because of constant data member
  A (int a): id (a)
  {
    std::cout << "A user defined constructor" << std::endl;
  }
  A (const A &a): id (a.id)
  {
    std::cout << "A copy constructor" << std::endl;
  }
  ~A ()
  {
    std::cout << "A destructor" << std::endl;
  }
private:
  const int id;
};

class B
{
public:
  // must use initializer because of no default constructor for A
  B (int a): id (a)
  {
    std::cout << "B constructor 1" << std::endl;
  }
  B (A id): id (id)
  {
    std::cout << "B constructor 2" << std::endl;
  }
  ~B ()
  {
    std::cout << "B destructor" << std::endl;
  }
private:
  A id;
};

int main ()
{
  B b (10);
  std::cout << "#########" << std::endl;
  A a (10);
  B c (a);
  std::cout << "#########" << std::endl;
  B d (A {10});
  std::cout << "#########" << std::endl;

  return 0;
}
