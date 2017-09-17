#include <iostream>
using namespace std;

// Dynamic programming. start from the right bottom corner.
// 1, must be alive in any location.
// 2, with the minimum required blood.

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

int dungeon_problem (int array[][3], int row, int col)
{
  int result;
  int **dp = new int *[row];
  for (unsigned i = 0; i < row; ++i)
    dp[i] = new int [col];

  if (array[row-1][col-1] > 0)
    dp[row-1][col-1] = 1;
  else
    dp[row-1][col-1] = 1 - array[row-1][col-1];


  for (int i = row - 2; i >= 0; --i)
    dp[i][col-1] = MAX (dp[i+1][col-1] - array[i][col-1], 1);

  for (int i = col - 2; i >= 0; --i)
    dp[row-1][i] = MAX (dp[row-1][i+1] - array[row-1][i], 1);

  for (int i = row - 2; i >= 0; --i)
    for (int j = col - 2; j >= 0; --j)
      dp[i][j] = MAX (MIN (dp[i+1][j], dp[i][j+1]) - array[i][j], 1);

  result = dp[0][0];

  for (unsigned i = 0; i < col; ++i)
    delete dp[i];
  delete dp;
  return result;
}


int main ()
{
  int array[3][3] = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};

  int res = dungeon_problem (array, 3, 3);
  cout << res << endl;
  return 0;
}
