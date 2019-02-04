#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
class Solution {
public:
  /*
  DP[0][0] 代表都为空字符的情况
  DP[i][j] 表示s[0:i-1]与p[0:j-1]匹配
  */
  bool isMatch (string s, string p)
    {
      unsigned s_size = s.size();
      unsigned p_size = p.size();
      unsigned DP[s_size+1][p_size+1];
      DP[0][0] = 1;

      for (int i = 1; i <= s_size; ++i)
	DP[i][0] = 0;
      for (int j = 1; j <= p_size; ++j)
	{
	  if (p[j-1] == '*')
	    DP[0][j] = DP[0][j-2];
	  else
	    DP[0][j] = 0;
	}

      if (s_size == 0 || p_size == 0)
	return DP[s_size][p_size];

      for (int i = 0; i < s_size; ++i)
	for (int j = 0; j < p_size; ++j)
	  {
	    if (p[j] == '*')
	      {
		if (j >= 1 && DP[i+1][j-1])
		  DP[i+1][j+1] = 1;
		else if ((p[j-1] == s[i] || p[j-1] == '.') && DP[i][j+1])
		  DP[i+1][j+1] = 1;
		else
		  DP[i+1][j+1] = 0;
	      }
	    else if (p[j] == '.')
	      DP[i+1][j+1] = DP[i][j];
	    else
	      {
		DP[i+1][j+1] = DP[i][j] && (s[i] == p[j]);
	      }
	  }

      for (int i = 1; i <= s_size; ++i)
	for (int j = 1; j <= p_size; ++j)
	  cout << "i: " << i << " j: " << j << ", " <<  DP[i][j] << endl;

      return DP[s_size][p_size];
    }
};

int main ()
{
  Solution solution;

  string input, pattern;
  while (1)
    {
      cout << "please give a string: ";
      cin >> input;
      cout << "please give a pattern: ";
      cin >> pattern;

      cout << solution.isMatch (input, pattern) << endl;
    }
}
