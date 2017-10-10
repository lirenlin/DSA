#include <iostream>
#include <string>

using namespace std;

int min (int a, int b, int c)
{
  int tmp = a > b? b : a;
  return (tmp > c? c: tmp);
}

int editDistance (string str1, string str2)
{

  int size1 = str1.size ();
  int size2 = str2.size ();

  int dp[size1+1][size2+1];

  for (int i = 0; i <= size1; i++)
    for (int j = 0; j <= size2; j++)
      {
	if (i == 0)
	  dp[i][j] = j;
	else if (j == 0)
	  dp[i][j] = i;
	else if (str1[i] == str2[j])
	  dp[i][j]= dp[i-1][j-1];
	else
	  dp[i][j] = 1 + min (dp[i-1][j],	// remove
			      dp[i][j-1],	// insert
			      dp[i-1][j-1]);	// replace
      }

  return dp[size1][size2];
}

int main ()
{
  string str1 = "lirenlin";
  string str2 = "libeibei";
  string str3 = "renlinli";

  cout << str1 << " --> " << str2 << ": edit distance ";
  cout << editDistance (str1, str2);
  cout << endl;

  cout << str1 << " --> " << str3 << ": edit distance ";
  cout << editDistance (str1, str3);
  cout << endl;

  return 0;
}
