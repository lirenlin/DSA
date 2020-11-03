// https://stackoverflow.com/questions/4622330/operator-overloading-member-function-vs-non-member-function
#include <iostream>

class Dummy
{
public:
  Dummy(int x): a(x) {}

  Dummy operator + (const Dummy& other) {a += other.a; return *this;}
  int getResult() const {return a;}
  friend Dummy operator+ (int left, const Dummy& right) {return Dummy(left + right.a);}

private:
  int a = 0;
};

int main ()
{
  Dummy dummy = {10};
  dummy = 10 + dummy;
  std::cout << dummy.getResult() << std::endl;

}
