#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct {
    bool operator () (int a, int b) const
      {
	int a_tmp = a, b_tmp = b;
	int sum_ab = a, sum_ba = b;

	while (b_tmp > 0)
	  {
	    b_tmp = b_tmp / 10;
	    sum_ab *= 10;
	  }
	sum_ab += b;

	while (a_tmp > 0)
	  {
	    a_tmp = a_tmp / 10;
	    sum_ba *= 10;
	  }
	sum_ba += a;

	if (sum_ab > sum_ba)
	  return true;
	else
	  return false;
      }
} customLarge;

int main ()
{
  std::vector<int> a = {3, 30, 34, 5, 9};
  std::sort (a.begin (), a.end (), customLarge);

  for (auto val: a)
    cout << val;
  cout << endl;

  return 0;
}
