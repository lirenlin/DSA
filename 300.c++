// Longest Increasing Subsequence
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int lengthOfLIS (vector<int> &nums) {
      for (int i = 0; i < nums.size (); ++i)
	dp.push_back (1);

      //return LISTopDown (nums, nums.size ());
      //return LISTopDownDP (nums, nums.size ());
      return LISDP (nums);
  }
private:
  int LISTopDown (vector<int> &nums, int i);
  int LISTopDownDP (vector<int> &nums, int i);
  int LISDP (vector<int> &nums);
  vector <int> dp;
};

// topdown Recursive
int Solution::LISTopDown (vector<int> &nums, int i)
{
  if (i == 0)
    return 0;
  if (i == 1)
    return 1;
  if (i == 2)
    return nums[1] > nums[0]? 2:1;

  int max = 1;

  for (int j = 0; j < i; j++)
    {
      int val = LISTopDown (nums, j);
      if (nums[i] > nums[j])
	val += 1;
      max = (val > max)? val : max;
    }

  return max;
}

// topdown Recursive with memoization
int Solution::LISTopDownDP (vector<int> &nums, int i)
{
  if (i == 0)
    return 1;

  int val = 0;
  int max = 1;

  for (int j = 0; j < i; j++)
    {
      if (dp[j] > 1)
	val = dp[j];
      else
	val = LISTopDownDP (nums, j);

      if (nums[i] > nums[j])
	{
	  val += 1;
	  dp[i] = val;
	}

      max = (val > max)? val : max;
    }

  return max;
}

// buttom up DP
int Solution::LISDP (vector<int> &nums)
{
  int size = nums.size ();
  if (size == 0)
    return 0;
  else if (size == 1)
    return 1;

  // the longest instreasing sequence ending at i;
  int dp[size];
  int max = 1;
  dp[0] = 1;

  for (int i = 1; i < size; ++i)
    {
      dp[i] = 1;
      int local_max = 1;
      for (int j = 0; j < i; ++j)
	{
	  int val = dp[j];
	  if (nums[j] < nums[i])
	    {
	      val += 1;
	      if (val > local_max)
		local_max = val;
	    }
	}
      dp[i] = local_max;
      max = (max < local_max) ? local_max : max;
    }

  return max;
}

int
main ()
{
  //vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
  //vector<int> nums = {4,10,4,3,8,9};
  vector<int> nums = {1,3,6,7,9,4,10,5,6};
  Solution solution;

  int res = solution.lengthOfLIS (nums);
  cout << res << '\n';

  return 0;
}
