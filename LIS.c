//longest increasing subsequence
#include <stdio.h>
#include <stdlib.h>

int lis (int array[], int n)
{
  int *dp, i, j, max = 0;
  dp = (int *)malloc (sizeof (int) * n);

  for (i = 0; i < n; ++i)
    dp[i] = 1;

  for (i = 1; i < n; ++i)
    for (j = 0; j < i; ++j)
      if (dp[i] < dp[j] + 1 && array[i] > array[j])
	dp[i] = dp [j] + 1;

  for (i = 0; i < n; ++i)
    if (max < dp[i])
      max = dp[i];

  free (dp);
  return max;
}

int main()
{
  int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("Length of lis is %d\n", lis( arr, n ) );
  return 0;
}
