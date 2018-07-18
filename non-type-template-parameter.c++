#include <iostream>
using namespace std;

enum class RegClass {INT, FLOAT, DOUBLE, VEC};

template <int Val, RegClass Rc> class Register;
template <int val, RegClass Rc>
ostream& operator<< (ostream &os, const Register<val, Rc> &reg)
{
  os << reg.getName ();
  return os;
}

template <int Val, RegClass regclass>
class Register {
public:
  Register (): rclass (regclass) {};

  friend ostream& operator<< <Val, regclass> (ostream &os, const Register &reg);
private:
  const RegClass rclass;
  string getName () const {return to_string (Val);};
};

int main ()
{
  Register<1, RegClass::INT> reg;
  cout << reg << endl;
}
