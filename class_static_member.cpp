#include <iostream>
using namespace std;

class Dummy
{
public:
  static char ID;
};
char Dummy::ID = 0;

int main ()
{
  char *ptr = &Dummy::ID;
  if (ptr == 0)
    cout << "zero" << endl;
  else
    cout << "non-zero" << endl;
}
