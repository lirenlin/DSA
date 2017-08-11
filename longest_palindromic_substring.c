void printSubStr (char *str, int low, int high)
{
  for (int i = low; i <= high; ++i)
    printf ("%c", str[i]);
}

int longestPalSubstr (char *str)
{
  int len = strlen (str);
  bool dp[n][n];
  memset (dp, 0, sizeof (dp));

  int start = 0;
  for (int i = 0; i < n-1; ++i)
    if (str[i] == str[i+1])
      dp[i][i+1] = true;

}
