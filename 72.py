def min_distance (str1, str2):
    m = len (str1)
    n = len (str2)
    dp = [[0 for __ in range (m + 1)] for __ in range (n+1)]

    for i in range (m+1):
        dp[0][i] = i
    for i in range (n+1):
        dp[i][0] = i
    for i in range (1, n+1):
        for j in range (1, m+1):
            onemore = 1 if str1[j-1] != str2[i-1] else 0
            dp[i][j] = min (dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + onemore)

    return dp[n][m]

print min_distance ("faf", "efef")
