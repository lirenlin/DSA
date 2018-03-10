#include <iostream>
using namespace std;

void print_substr (string &str, int i, int j)
{
  cout << str.substr (i, j+1-i) << endl;
}

void solution_dp (string str)
{
  unsigned size = str.size ();
  unsigned idx = 0;
  bool dp[size][size];
  unsigned len = 0;
  unsigned start = 0;

  for (unsigned i = 0; i < size; i++)
    for (unsigned j = 0; j < size; j++)
      dp[i][j] = false;

  while (idx < size - 1)
    {
      dp[idx][idx] = true;
      if (str[idx] == str[idx+1])
	{
	  dp[idx][idx+1] = true;
	  dp[idx+1][idx] = true;
	}
      idx++;
    }
  dp[idx][idx] = true;

  for (unsigned len = 1; len < size; ++len)
    for (unsigned idx = 1; len + idx < size; ++idx)
      {
	if (dp[idx][idx+len-1] && str[idx-1] == str[idx+len])
	  dp[idx-1][idx+len] = true;
	else
	  dp[idx-1][idx+len] = false;
      }
  for (idx = 0; idx < size; ++idx)
    for (unsigned j = idx; j < size; ++j)
      if (dp[idx][j])
	print_substr (str, idx, j);
}

int main ()
{
  string str;
  cout << "Give a string: ";
  cin >> str;
  solution_dp (str);

  return 0;
}
