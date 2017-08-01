def editDistance (str1, str2):
    m = len (str1)
    n = len (str2)
    dp = [[0 for _ in range (n)] for _ in range (m)]

    for i in range (m):
        dp[i][0] = i
    for i in range (n):
        dp[0][i] = i

    for i in range (1, m):
        for j in range (1, n):
            if str1[i] == str2[j]:
                dp[i][j] = dp[i-1][j-1]
            else:
                dp[i][j] = 1 + min (dp[i][j-1], dp[i-1][j], dp[i-1][j-1])


    return dp[m-1][n-1]


str1 = "sunday"
str2 = "saturday"

print editDistance (str1, str2)
