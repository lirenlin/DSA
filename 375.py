class Solution (object):
  def getMoneyAmount(self, n):
    def result (dp, start, end):
      if start >= end:
        return 0

      if dp[start][end] != -1:
        return dp[start][end]

      for i in range (start, end):
        val_left = result (dp, start, i-1)
        val_right = result (dp, i+1, end)
        val = max (val_left, val_right) + i

        if dp[start][end] == -1:
          dp[start][end] = val
        else:
          dp[start][end] = min (dp[start][end], val)

      return dp[start][end]


    if n == 0 or n == 1:
        return 0
    elif n == 2:
        return 1
    elif n == 3:
        return 2
    elif n == 4:
        return 4
    elif n == 5:
        return 6
    dp = [[-1 for i in range (n+1)] for i in range (n+1)]
    dp[0][0] = 0
    dp[0][1] = 0
    dp[0][2] = 1
    dp[0][3] = 2
    dp[0][4] = 4
    dp[0][5] = 6

    res = result(dp, 1, n)
    return res

solution = Solution ()
print solution.getMoneyAmount (21)
