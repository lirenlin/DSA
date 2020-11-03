#include <iostream>
#include <cmath>

template <int m>
void naive(float A[m][m], float B[m][m], float C[m][m])
{
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      float res = 0;
      for (int k = 0; k < m; ++k) {
	res += A[i][k] * B[k][j];
      }
      C[i][j] = res;
    }
  }
}

template <int m>
void blocking3(float A[m][m], float B[m][m], float C[m][m])
{
  int block = 3;
  for (int i = 0; i < m; i+=3) {
      for (int j = 0; j < m; j+=3) {
	  float sum1 = 0;
	  float sum2 = 0;
	  float sum3 = 0;
	  float sum4 = 0;
	  float sum5 = 0;
	  float sum6 = 0;
	  float sum7 = 0;
	  float sum8 = 0;
	  float sum9 = 0;
	  for (int k = 0; k < m; k += 3) {
	      float a11 = A[i][k];
	      float a12 = A[i][k+1];
	      float a13 = A[i][k+2];
	      float a21 = A[i+1][k];
	      float a22 = A[i+1][k+1];
	      float a23 = A[i+1][k+2];
	      float a31 = A[i+2][k];
	      float a32 = A[i+2][k+1];
	      float a33 = A[i+2][k+2];

	      float b11 = B[k][j];
	      float b12 = B[k][j+1];
	      float b13 = B[k][j+2];
	      float b21 = B[k+1][j];
	      float b22 = B[k+1][j+1];
	      float b23 = B[k+1][j+2];
	      float b31 = B[k+2][j];
	      float b32 = B[k+2][j+1];
	      float b33 = B[k+2][j+2];

	      sum1 += a11 * b11 + a12 * b21 + a13 * b31;
	      sum2 += a11 * b12 + a12 * b22 + a13 * b32;
	      sum3 += a11 * b13 + a12 * b23 + a13 * b33;

	      sum4 += a21 * b11 + a22 * b21 + a23 * b31;
	      sum5 += a21 * b12 + a22 * b22 + a23 * b32;
	      sum6 += a21 * b13 + a22 * b23 + a23 * b33;

	      sum7 += a31 * b11 + a32 * b21 + a33 * b31;
	      sum8 += a31 * b12 + a32 * b22 + a33 * b32;
	      sum9 += a31 * b13 + a32 * b23 + a33 * b33;
	  }
	  C[i][j] = sum1;
	  C[i][j+1] = sum2;
	  C[i][j+2] = sum3;
	  C[i+1][j] = sum4;
	  C[i+1][j+1] = sum5;
	  C[i+1][j+2] = sum6;
	  C[i+2][j] = sum7;
	  C[i+2][j+1] = sum8;
	  C[i+2][j+2] = sum9;
      }
  }
}

template <int m>
void blocking2(float A[m][m], float B[m][m], float C[m][m])
{
  int block = 2;
  for (int i = 0; i < m; i+=block) {
      for (int j = 0; j < m; j+=block) {
	  float sum1 = 0;
	  float sum2 = 0;
	  float sum3 = 0;
	  float sum4 = 0;
	  float sum5 = 0;
	  float sum6 = 0;
	  float sum7 = 0;
	  float sum8 = 0;
	  float sum9 = 0;
	  for (int k = 0; k < m; k += block) {
	      sum1 += A[i][k] * B[k][j] + A[i][k+1] * B[k+1][j];
	      sum2 += A[i][k] * B[k][j+1] + A[i][k+1] * B[k+1][j+1];
	      sum3 += A[i+1][k] * B[k][j] + A[i+1][k+1] * B[k+1][j];
	      sum4 += A[i+1][k] * B[k][j+1] + A[i+1][k+1] * B[k+1][j+1];
	  }
	  C[i][j] = sum1;
	  C[i][j+1] = sum2;
	  C[i+1][j] = sum3;
	  C[i+1][j+1] = sum4;
      }
  }
}

template <int m>
bool cmp(float A[m][m], float B[m][m])
{
  for (int i = 0; i< m; ++i) {
    for (int j = 0; j< m; ++j) {
	if (std::fabs(A[i][j] - B[i][j]) > 1e-5) {
	  std::cout << "no equal\n";
	  return false;
	}
    }
  }
  return true;
}

template <int m>
float sum(float A[m][m])
{
  float sum = 0;
  for (int i = 0; i< m; ++i) {
    for (int j = 0; j< m; ++j) {
	sum += A[i][j];
    }
  }
  return sum;
}

int main()
{
  const int n = 600;
  float A[n][n];
  float B[n][n];
  for (int i = 0; i< n; ++i) {
    for (int j = 0; j< n; ++j) {
      A[i][j] = i / 2.0;
      B[i][j] = i / 3.0;
    }
  }

  float C[n][n] = {0};
  blocking3<n>(A, B, C);
  auto val = sum<n>(C);

  //cmp<n>(C, C_new);

  /*
  for (int i = 0; i< n; ++i) {
    for (int j = 0; j< n; ++j) {
	std::cout << C[i][j] << " ";
    }
    std::cout << std::endl;
  }
  */

  return val;
}
