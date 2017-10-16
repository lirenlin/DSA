#include <iostream>
#include <iomanip>
using namespace std;

template <typename T>
void matrixMul (T *A, T *B, T *c, int m, int n)
{
  for (unsigned i = 0; i < m; i++)
    for (unsigned j = 0; j < n; j++)
      {
	unsigned index = i * n + j;
	c[index] = 0;
	for (unsigned k = 0; k < n; k++)
	  c[index] += A[i*n + k] * B[k*n+j];
      }
}

#define ROW 3
#define COL 3
int main ()
{
  double A[3][3] = {{1.0, 2.0, 3.0},
	{4.0, 5.0, 6.0},
	{7.0, 8.0, 9.0}};
  double B[3][3] = {{2.0, -2.0, 1.0},
	{1.0, 3.0, 9.0},
	{17.0, -3.0, 7.0}};

  double res[ROW][COL];
  matrixMul<double> (A[0], B[0], res[0], ROW, COL);

  for (unsigned i = 0; i < ROW; ++i)
    {
      for (unsigned j = 0; j < ROW; ++j)
	cout << setw (5) << res[i][j];
      cout << endl;
    }

  return 0;
}
