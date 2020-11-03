#include <iostream>
#include <vector>

struct Point3s
{
  int x;
  int y;
  int z;
};

template <typename T>
class sdlt_internal_data { };

#define SDLT_PREMITIVE_1(POD_TYPE, member) \
  std::vector<decltype(std::declval<POD_TYPE>().member)> member;

#define SDLT_PREMITIVE_2(POD_TYPE, member, ...) \
  std::vector<decltype(std::declval<POD_TYPE>().member)> member; \
  SDLT_PREMITIVE_1(POD_TYPE, __VA_ARGS__)

#define SDLT_PREMITIVE_3(POD_TYPE, member, ...) \
  std::vector<decltype(std::declval<POD_TYPE>().member)> member; \
  SDLT_PREMITIVE_2(POD_TYPE, __VA_ARGS__)

#define SDLT_PREMITIVE_4(POD_TYPE, member, ...) \
  std::vector<decltype(std::declval<POD_TYPE>().member)> member; \
  SDLT_PREMITIVE_3(POD_TYPE, __VA_ARGS__)

#define SDLT_PREMITIVE_5(POD_TYPE, member, ...) \
  std::vector<decltype(std::declval<POD_TYPE>().member)> member; \
  SDLT_PREMITIVE_4(POD_TYPE, __VA_ARGS__)

#define FOR_EACH_NARG(...) FOR_EACH_ARG_N_(__VA_ARGS__, FOR_EACH_RSEQ())
#define FOR_EACH_ARG_N_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, N, ...) N
#define FOR_EACH_RSEQ() 5, 4, 3, 2, 1, 0

#define CONCATENATE(PREFIX, N) PREFIX##N
#define SDLT_PREMITIVE_(N, POD_TYPE, member1, ...) CONCATENATE(SDLT_PREMITIVE_, N)(POD_TYPE, member1, __VA_ARGS__)
#define SDLT_PREMITIVE(POD_TYPE, member1, ...) \
  template <>					\
  class sdlt_internal_data<POD_TYPE> { \
  public: \
      SDLT_PREMITIVE_(FOR_EACH_NARG(member1, __VA_ARGS__), POD_TYPE, member1, __VA_ARGS__) \
  };


SDLT_PREMITIVE(Point3s, x, y, z)

namespace sdlt
{
  template <typename T, int size>
    class soa1d_container
      {
    public:
      soa1d_container() {}
      T& operator[] (std::size_t idx);
      const T& operator[] (std::size_t idx) const;

    private:
      sdlt_internal_data<T> data;
      };

  template<typename T, int size>
    inline
    T& soa1d_container<T, size>::operator[] (std::size_t idx)
      {
	return T{data.x[idx], data.y[idx], data.z[idx]};
      }
  template<typename T, int size>
    inline
    const T& soa1d_container<T, size>::operator[] (std::size_t idx) const
      {
	return T{data.x[idx], data.y[idx], data.z[idx]};
      }
}

int main()
{
  const sdlt::soa1d_container<Point3s, 10> input;
  std::cout << input[0].z << std::endl;
  std::cout << input[1].z << std::endl;
  return 0;
}
