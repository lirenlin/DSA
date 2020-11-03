#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

template <template<class, class...> class H, class T>
void f(const H<T> &value) {
    std::copy(value.begin(), value.end(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << "generic implementation\n";
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}
template <typename H>
void foo(const H &value) {
    //with auto, no type is need to specify
    typedef decltype(value.back()) T;
    std::copy(value.begin(), value.end(), std::ostream_iterator<T>(std::cout, " "));
    std::cout << "no template template\n";
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

// template function cannot do partial specialization
template <template<class,class...> class H>
void f(const H<int> &value) {
    std::copy(value.begin(), value.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "int overloading\n";
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <template<class, class...> class H, class T>
class Container
{
public:
  Container(const H<T>& val): val_(val) {
      std::cout << "generic container\n";
  }
private:
  H<T> val_;
};

template <template<class, class...> class H>
class Container<H, int>
{
public:
  Container(const H<int>& val): val_(val) {
    std::cout << "container int partial specialization\n";
  }
private:
  H<int> val_;
};

int main()
{
  const std::vector<int> vec_int = {1, 2, 3};
  const std::vector<float> vec_float = {2.0, 3.0};
  const std::list<float> list_float = {2.0, 3.0};
  const std::list<int> list_int = {2, 3};
  //The compiler can deduce template type argument from function argument
  f(vec_int);
  f(vec_float);

  f(list_int);
  f(list_float);
  foo(list_float);

  //The compiler cannot deduce template type from constructor
  Container<std::vector, int> vec_int_con {vec_int};
  Container<std::list, float> list_float_con {list_float};

  return 0;
}
