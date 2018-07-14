//dynamic programming
//? matches any single character, * matches zero or more characters
//dp[i][j], the first i characters in string match the first j characters in
//the pattern

#include <iostream>
#include <string>

inline bool isWildCard (char a)
{
  return ((a == '?') || (a == '*'));
}

inline bool matchChar (char a, char pat)
{
  return ((a == pat) || (pat == '?') || (pat == '*'));
}

bool tryToMatch (std::string str, std::string pattern)
{
  unsigned strLen = str.size ();
  unsigned patternLen = pattern.size ();

  // initialized all as false
  bool dp[strLen + 1][patternLen + 1] = {};
  dp[0][0] = true;

  for (int i = 1; i < patternLen + 1; ++i)
    dp[0][i] = (dp[0][i-1] && pattern[i] == '*');

  for (int j = 1; j <= patternLen; ++j)
    for (int i = 1; i <= strLen; ++i)
      {
	if (pattern[j-1] == '*')
	  dp[i][j] = dp[i-1][j] || dp[i-1][j-1];
	else if (pattern[j-1] == '?')
	  dp[i][j] = dp[i-1][j-1];
	else if (str[i-1] == pattern[j-1])
	  dp[i][j] = dp[i-1][j-1];
	else
	  dp[i][j] = false;
      }

  for (int i = 0; i <= strLen; ++i)
    {
      for (int j = 0; j <= patternLen; ++j)
	std::cout << dp[i][j] << " ";
      std::cout << std::endl;
    }

  return dp[strLen][patternLen];
}


int main ()
{
  std::string str;
  std::string pattern;
  std::cout << "Give a string: ";
  std::cin >> str;
  std::cout << "Give a pattern: ";
  std::cin >> pattern;
  if (tryToMatch (str, pattern))
    std::cout << "matched!" << std::endl;
  else
    std::cout << "doesn't matched!" << std::endl;

  return 0;
}
