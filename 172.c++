#include <iostream>
using namespace std;

int trailingZeroes (int num)
{
  unsigned n = num;
  unsigned count = 0;

  while (n = n / 5)
    count += n;

  return count;
}

int main ()
{
  int num;
  cout << "enter a number: ";
  cin >> num;
  cout << trailingZeroes (num) << endl;
  return 0;
}
