def isInterleave (s1, s2, s3):
    m = len (s1)
    n = len (s2)
    l = len (s3)
    if m + n != l:
        return False
    dp = [[True for __ in range (m+1)] for __ in range (n+1)]

    for i in range (1, m+1):
        dp[i][0] = dp[i-1][0] and s1[i-1] == s3[i-1]
    for i in range (1, n+1):
        dp[0][i] = dp[0][i-1] and s2[i-1] == s3[i-1]

    for i in range (1, m+1):
        for j in range (1, n+1):
            dp[i][j] = (dp[i-1][j] and s1[i-1] == s3[i+j-1]) or (dp[i][j-1] and s2[j-1] == s3[i+j-1])

    return dp[m][n]

print isInterleave ("aabcc", "dbbca", "aadbbcbcac")
print isInterleave("aabcc", "dbbca", "aadbbbaccc")

