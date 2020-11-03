#include <iostream>
#include <string>

//In reverse order of construction: First constructed, last destructed.

template <typename T>
struct Temp
{
 T _val;
  Temp(T val="temp"): _val(val) {std::cout << "ctor: " <<  _val << std::endl;}
  ~Temp() {std::cout << "dtor: " << _val << std::endl;}
};

template <typename T>
Temp<T> func() { return Temp<T>();}

int main ()
{
  Temp<std::string> a("A");
  Temp<std::string> b("B");
  func<std::string>();
  Temp<std::string> c("C");

  return 0;
}
