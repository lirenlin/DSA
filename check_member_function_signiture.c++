#include <iostream>
#include <type_traits>
using namespace std;

struct A {
    void operator() (int a, int b) const {cout << "2\n";}
};
struct B {
    void operator()(int a) const { cout << "1\n";}
};

// Primary template with a static assertion
// for a meaningful error message
// if it ever gets instantiated.
// We could leave it undefined if we didn't care.

template<typename, typename T>
struct functor_match {
    static_assert(
		  std::integral_constant<T, false>::value,
		  "Second template parameter needs to be of function type.");
};

// specialization that does the checking

template<typename C, typename Ret, typename... Args>
struct functor_match<C, Ret(Args...)> {
private:
  template<typename T>
    static constexpr auto check(T*)
    -> typename
    std::is_same<
    decltype( std::declval<T>()( std::declval<Args>()... ) ),
    Ret    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
      >::type;  // attempt to call it and see if the return type is correct

  template<typename>
    static constexpr std::false_type check(...);

  typedef decltype(check<C>(0)) type;

public:
  static constexpr bool value = type::value;
};

template <typename T, typename = std::enable_if_t<functor_match<T, void(int, int)>::value>>
void call(const T& obj, int p1, int p2)
{
  obj(p1, p2);
}

template <typename T, typename = std::enable_if_t<functor_match<T, void(int)>::value>>
void call(const T& obj, int p1)
{
  obj(p1);
}

int main()
{
  A a;
  B b;
  call(a, 10, 11);
  call(b, 10);
  return 0;
}

