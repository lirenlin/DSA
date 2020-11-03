#include <iostream>

void afunc()
{
  std::cout << "global func\n";
}

class Foo
{
public:
  virtual void afunc()
    {
      std::cout << "Foo func\n";
    }
private:
  int a;
};

class Bar
{
public:
  virtual void bfunc()
    {
      std::cout << "Bar func\n";
    }
};

template <typename... T>
class Derive: public T...
{
public:
  using self = Derive<T...>;
  void tfunc()
    {
      self::afunc();
      afunc();
    }
  void afunc()
    {
      std::cout << "Derive func\n";
    }
  void bfunc()
    {
      std::cout << "Derive func\n";
    }
};

int main()
{
  Derive<Foo, Bar> obj;
  Derive<Foo, Bar> *ptr = &obj;
  ptr->afunc();
  ptr->bfunc();
  Foo *ptr_foo = &obj;
  Bar *ptr_bar = &obj;
  std::cout << ptr_foo << std::endl;
  std::cout << ptr_bar << std::endl;
  std::cout << (char*)ptr_bar - (char*)ptr_foo << std::endl;
  std::cout << sizeof (Foo) << std::endl;
  std::cout << sizeof (void *) << std::endl;
  std::cout << sizeof (int) << std::endl;

  return 0;
}
