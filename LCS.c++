#include <iostream>
#include <string>
using namespace std;

int
longestCommonSubstring (string A, string B)
{
  int sizeA = A.size ();
  int sizeB = B.size ();

  int dp[sizeA][sizeB];
  for (int i = 0; i < sizeA; ++i)
    {
      if (A[0] == B[i])
	dp[0][i] = 1;
      else
	dp[0][i] = 0;

      if (A[i] == B[0])
	dp[i][0] = 1;
      else
	dp[i][0] = 0;
    }

  int max = 0;
  for (int i = 1; i < sizeA; ++i)
    for (int j = 1; j < sizeA; ++j)
      {
	int val;
	if (A[i] == B[j])
	  val = dp[i-1][j-1] + 1;
	else
	  val = 0;
	dp[i][j] = val;

	if (max < val)
	  max = val;
      }
  return max;
}

int
main ()
{
  string A;
  string B;
  cout << "give first string: ";
  cin >> A;
  cout << "give second string: ";
  cin >> B;

  int val = longestCommonSubstring (A, B);
  cout << val << endl;
  return 0;


}
