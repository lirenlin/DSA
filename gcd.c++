#include <iostream>
using namespace std;

// Euclidean algorithm, check the wiki
int gcd (int a, int b)
{
  if (a == b || b == 0)
    return a;
  else if (a == 0)
    return b;

  while (a != b)
    {
      if (a > b)
	a -= b;
      else
	b -= a;
    }
  return a;
}

int gcd2 (int a, int b)
{
  if (b == 0 || a == b)
    return a;
  else if (a == 0)
    return b;

  int first = b;
  int second = a % b;
  while (second)
    {
      int tmp = second;
      second = first % second;
      first = tmp;
    }

  return first;
}

int
main ()
{
  int a, b;
  cout << "give first number: ";
  cin >> a;
  cout << "give second number: ";
  cin >> b;

  int res = gcd (a, b);
  cout << "gcd of " << a << ", " << b << " is " << res << endl;
  res = gcd2 (a, b);
  cout << "gcd of " << a << ", " << b << " is " << res << endl;
  return 0;

}
