#include <iostream>
using namespace std;
class Dummy
{
public:
  void const_method () const {cout << __FUNCTION__ << endl;}
  void normal_method () {cout << __FUNCTION__ << endl;}
};

void print (const Dummy &obj)
{
  obj.const_method ();			//Okay
  //obj.normal_method ();		//wrong
}

int main ()
{
  const Dummy const_dummy;
  const_dummy.const_method (); 		//Okay
  //const_dummy.normal_method ();	//wrong
  print (const_dummy);

  Dummy dummy;
  print (dummy);			//Okay
  dummy.const_method ();		//Okay
  dummy.normal_method ();		//wrong
}
