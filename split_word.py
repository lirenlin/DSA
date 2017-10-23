import collections

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

def wb_recursive (string, wordDict):
  dic = collections.defaultdict(list)

  # return the list of word for string s
  def dfs (s):
    if not s:
      return [None]

    #if we already visited this string
    if s in dic:
      return dic[s]

    res = list ()
    for word in wordDict:
      n = len (word)
        # if the string start with word
      if word == s[:n]:
        for r in dfs (s[n:]):
          if r:
            res.append (word + " " + r)
          else:
            res.append (word)

    dic[s] = res
    return res

  return dfs (string)

string = "Iwanttoworkinshanghai"
wordDict = ("I", "want", "to", "work", "in", "shang" "hai", "shanghai", "wantto")
print wordBreak (string, wordDict)

res_list = wb_recursive (string, wordDict)
print min (res_list, key = len)
