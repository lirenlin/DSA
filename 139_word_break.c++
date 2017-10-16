#include <iostream>
#include <string>
#include <set>

using namespace std;
typedef set<string> wordDict;

bool wordBreak_back (string str, wordDict &dict)
{
  bool result = false;
  unsigned size = str.size ();
  unsigned count = 0;

  int *dp = new int[size];
  for (int i = 1; i < size; ++i)
   dp[i] = 0;

  for (int i = 0; i < size; ++i)
    for (int j = i; j >= 0; j--)
      {
	string word = str.substr (j, i-j+1);
	if (dict.find (word) != dict.end ())
	  if (j == 0 || dp[j-1] == 1)
	    {
	      dp[i] = 1;
	      break;
	    }

	count++;
	//cout << word << ": " << dp[i] << endl;
      }

  cout << __FUNCTION__ << ": " << count << endl;
  for (int i = 0; i < size; i++)
    cout << dp[i] << ' ';
  cout << endl;

  result = dp[size-1];
  delete[] dp;
  return result;
}

bool wordBreak_forward (string str, wordDict &dict)
{
  bool result = false;
  unsigned size = str.size ();
  unsigned count = 0;

  int *dp = new int[size];
  for (int i = 1; i < size; ++i)
   dp[i] = 0;

  for (int i = 0; i < size; ++i)
    for (int j = i; j < size; ++j)
      {
	/* Don't update dp.  */
	if (dp[j] == 1)
	  break;

	string word = str.substr (i, j-i+1);
	if (dict.find (word) == dict.end ())
	  dp[j] = 0;
	else
	  {
	    if (i == 0)
	      dp[j] = 1;
	    else
	      dp[j] = dp[i-1];
	  }
	count++;
	//cout << word << ": " << dp[j] << endl;
      }

  cout << __FUNCTION__ << ": " << count << endl;
  for (int i = 0; i < size; i++)
    cout << dp[i] << ' ';
  cout << endl;

  result = dp[size-1];
  delete[] dp;
  return result;
}

int main ()
{
  string str = "leetmecode";
  wordDict dict = {"leet", "code", "me", "mecode"};
  bool found1 = wordBreak_back (str, dict);
  bool found2 = wordBreak_forward (str, dict);

  if (found1 != found2)
    {
      cout << "two function result doesn't match" << endl;
      return 1;
    }

  cout << "dict: ";
  for (auto it : dict)
    cout << it << ' ';
  cout << endl;
  if (found1)
    cout << "split " << str << endl;
  else
    cout << "cannot split " << str << endl;

  return 0;
}
