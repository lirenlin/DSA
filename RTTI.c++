// https://en.wikipedia.org/wiki/Run-time_type_information
// dynamic_cast, type_info, typeid
// dynamic_cast of reference will throw exception when failed
// refernce could also be polymorphic
#include <iostream>
#include <typeinfo>
using namespace std;

class Base
{
public:
  virtual void tell () { cout << "Base" << endl;}
};

class Derive: public Base
{
public:
  void tell () { cout << "Derive" << endl;}
};
void my_function(Base& my_a)
{
    try {
        Derive& my_b = dynamic_cast<Derive&>(my_a); // cast will be successful only for Derive type objects.
        my_b.tell();
    }
    catch (const std::bad_cast& e) {
        std::cerr << "  Exception " << e.what() << " thrown." << std::endl;
        std::cerr << "  Object is not of type Derive" << std::endl;
    }
}

int main ()
{
  Base *base = new Base ();
  Base *derive = new Derive ();

  if (Derive *ptr = dynamic_cast<Derive *> (derive))
    ptr->tell ();

  // faster than dynamic_cast, just one comparison instead of whole inheritance
  // traversing
  if (typeid (derive) == typeid (base))
    {
      Base *base = static_cast <Base *> (derive);
      base->tell ();
    }

  my_function (*derive);

  cout << typeid (base).name () << endl;
  cout << typeid (derive).name () << endl;
  cout << typeid (*derive).name () << endl;

  return 0;
}
