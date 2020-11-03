#include <iostream>
#include <tuple>
#include <array>
#include <utility>

template <typename Array, size_t...I>
auto toTuple(const Array& val, std::index_sequence<I...>)
{
  return std::make_tuple(val[I]...);
}

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
auto a2t(const std::array<T, N>& val)
{
  return toTuple(val, Indices{});
}

int main()
{
  std::array<int, 4> array = {1, 2, 3, 4};
  auto tuple = a2t(array);

  std::cout << std::get<2>(tuple) << std::endl;
  return 0;
}




