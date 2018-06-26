#include <iostream>
#include <vector>
using namespace std;

using List = vector<int>;
int mcs (List list)
{
  // the max sum ending at i;
  // 1 2 -2 1
  // dp[0] = 1; dp[1]= 3; dp[2] = 1; dp[3] = 2
  int dp[list.size()];
  dp[0] = list[0];
  int max = dp[0];

  if (list.size() == 0)
    return 0;
  else if (list.size() == 1)
    return max;

  for (int i = 1; i < list.size (); ++i)
    {
      int tmp = dp[i-1] + list[i];
      int local_max = (tmp > list[i]) ? tmp:list[i];
      dp[i] = local_max;
      if (local_max > max)
	max = local_max;
    }
  return max;

}

int main ()
{
  List value = {1, 2, -2, 1};
  int a = mcs (value);
  cout << value << endl;
  cout << a << endl;
}
