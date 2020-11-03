#include <iostream>

class Foo
{
public:
  Foo(int i=0): _i(i) {}

  Foo& operator=(Foo&) {}
  Foo& operator=(Foo&) = default;

  Foo( Foo&&) = delete;
  Foo& operator=(Foo&&) = delete;

private:
  int _i;
};

void foo(Foo data);

int main()
{
  foo(Foo(10));
  Foo foo;
  foo = Foo(20);

  return 0;
}


