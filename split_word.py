def wordBreak (string, wordDict):
    n = len (string)
    dp = [0] * (n + 1)

    for i in range (n):
        min = -1
        for j in range (i, -1, -1):
            if j == 0 and string[j:i+1] in wordDict:
                min = 1;
            elif dp[j] > 0 and string[j:i+1] in wordDict:
                if min <= 0:
                    min = dp[j] + 1
                elif min > dp[j] + 1:
                    min = dp[j] + 1
        dp[i+1] = min

    return dp[n]

string = "Iwanttoworkinshanghai"
wordDict = {"I", "want", "to", "work", "in", "shang" "hai", "shanghai", "wantto"}
print wordBreak (string, wordDict)
