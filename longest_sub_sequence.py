def solution (list1, list2):
    if len (list1) == 0 or len (list2) == 0:
        return None

    n = len (list1)
    m = len (list2)
    dp = [[0 for _ in range (m)] for _ in range (n)]

    # boundary value
    for i in range (n):
        dp[i][0] = list1[i] == list2[0]
    for i in range (m):
        dp[0][i] = list1[0] == list2[i]

    for i in range (1, n):
        for j in range (1, m):
            # state transition
            if (list1[i] == list2[j]):
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max (dp[i-1][j], dp[i][j-1])

    return dp[n-1][m-1]

list1 = "AGGTAB"
list2 = "GXTXAYB"
print solution (list1, list2)
