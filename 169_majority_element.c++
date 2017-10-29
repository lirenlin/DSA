#include <iostream>
#include <list>

// g++ std=c++11
using namespace std;

int majorityElement (list<int> &array)
{
  int count = 0;
  int res;
  for(auto i : array)
    {
      if (count == 0)
	res = i;
      if (res == i)
	count += 1;
      else
	count -= 1;
    }

  return res;
}

int main ()
{
  list <int> array = {1, 2, 2, 3, 3, 1, 1, 1, 3};
  int res = majorityElement (array);
  cout << res << endl;

  array = {1, 2, 1, 3, 1, 4, 1, 5, 1};
  res = majorityElement (array);
  cout << res << endl;

  return 0;
}
