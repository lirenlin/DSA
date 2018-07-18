#include <iostream>
using namespace std;

enum class Type: unsigned {
  v1i8 = 0,
  v2i8 = 1,
  v3i8 = 2,
  v4i8 = 3,
  FIRST_INT_VEC = v1i8
};

int main ()
{
  //unsigned n =Type::FIRST_INT_VEC; //error: no scoped enum to in conversion
  cout << static_cast<int>(Type::FIRST_INT_VEC) << endl;;
  cout << static_cast<int>(Type::v1i8) << endl;
}

