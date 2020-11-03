#include <iostream>
#include <string>

// From the beginning
std::string LCSubStr_1(const std::string& X, const std::string& Y)
{
  size_t m = X.size();
  size_t n = Y.size();
  size_t DP[m+1][n+1];

  size_t max_len = 0;
  size_t max_index = 0;

  for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < n; ++j) {
	  if (i == 0 || j == 0) {
	      DP[i][j] = 0;
	  }

	  if (X[i] == Y[j]) {
	      DP[i+1][j+1] = 1 + DP[i][j];
	      if (DP[i+1][j+1] > max_len)
		{
		  max_len = DP[i+1][j+1];
		  max_index = i + 1 - max_len;
		}
	  }
	  else {
	      DP[i+1][j+1] = 0;
	  }
      }
  }

  return X.substr(max_index, max_len);
}

// from the end
std::string LCSubStr(const std::string& X, const std::string& Y)
{
  size_t m = X.size();
  size_t n = Y.size();
  size_t DP[m+1][n+1];

  size_t max_len = 0;
  size_t max_index = 0;

  for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
	  if (i == m - 1 || j == n -1) {
	      DP[i+1][j+1] = 0;
	  }
	  if (X[i] == Y[j]) {
	      DP[i][j] = 1 + DP[i+1][j+1];
	      if (DP[i][j] > max_len)
		{
		  max_len = DP[i][j];
		  max_index = i;
		}
	    }
	  else {
	    DP[i][j] = 0;
	  }
	}
    }

  return X.substr(max_index, max_len);
}

int main()
{
  auto X = "lirenlin";
  auto Y = "linrenl";
  auto subStr_1 = LCSubStr_1(X, Y);
  if (!subStr_1.empty())
    std::cout << subStr_1 << std::endl;

  auto subStr = LCSubStr(X, Y);
  if (!subStr.empty())
    std::cout << subStr << std::endl;

  return 0;
}

