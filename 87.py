def solution (s1, s2):
  if s1 == s2:
    return True

  size = len (s1)
  if size == 1:
    return s1 == s2
  elif size == 2:
    if s1[0] == s2[1] and s1[1] == s2[0]:
      return True
    else:
      return False

  #dp[len][i][j]: s1[i:i+len] --> s2[j:j+len]
  dp = [[[False for __ in range (size)] for __ in range (size)] for __ in range (size+1)]
  for i in range (size):
    for j in range (size):
      dp[1][i][j] = (s1[i] == s2[j])

  for i in range (2, size+1):
    for j in range (size-i+1):
      for k in range (size-i+1):
	r = False
	for a in range (1, i):
	  r = (dp[a][j][k] and dp[i-a][j+a][k+a]) or (dp[a][j][k+i-a] and dp[i-a][j+a][k])
	  if r:
	    break

	dp[i][j][k] = r

  return dp[size][0][0]

s1 = "rgtae"
s2 = "great"
print solution (s1, s2)
