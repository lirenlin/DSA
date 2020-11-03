#include <iostream>
#include <functional>

class Data {
public:
  Data (int a, int b): _a(a), _b(b) {}
  // deleted copy constructor, std::bind will fail because of this. It cannot
  // make a copy for the binding arguments. Instead std::ref could be used to
  // pass remove the copy operation
  Data (const Data&) = delete;

  int getResult() const {return _a + _b;}
  void inc() {_a++;}

private:
  int _a;
  int _b;

  // declaration doesn't affected by class access specifier
  friend std::ostream& operator<<(std::ostream &os, const Data& data);
};

std::ostream& operator<<(std::ostream &os, const Data& data)
{
  return os << &data << " data object: " << data._a << " " << data._b;
}


int foo_cref (const Data& data) {
    return data.getResult();
}

int foo_ref (Data& data) {
    data.inc();
    return data.getResult();
}

int main ()
{
  Data data(1,2);
  std::cout << data << std::endl;

  // This will fail as std::bind will copy or move the arguments. arguments are
  // never passed by reference unless wrapped in std::ref or std::cref
  // https://en.cppreference.com/w/cpp/utility/functional/bind
  auto fail_func = std::bind (foo_cref, data);

  auto cref_func = std::bind (foo_cref, std::cref(data));
  std::cout << cref_func() << std::endl;
  std::cout << data << std::endl;

  // value could be updated inside the function object
  auto func_ref = std::bind (foo_ref, std::ref(data));
  std::cout << func_ref() << std::endl;
  std::cout << data << std::endl;

  return 0;
}

