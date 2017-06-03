def min_path_sum (array):
  m = len (array)
  n = len (array [0])
  path = list ()

  dp = [[0 for __ in range (n)] for __ in range (m)]
  dp[0][0] = array[0][0]

  for i in range (1, m):
    dp[i][0] = array[i][0] + dp[i-1][0]
  for i in range (1, n):
    dp[0][i] = array[0][i] + dp[0][i-1]

  for i in range (1, m):
    for j in range (1, n):
      if dp[i][j-1] > dp[i-1][j]:
	print "down"
	path.append ('D')
	dp[i][j] = array[i][j] + dp[i-1][j]
      else:
	print "right"
	path.append ('R')
	dp[i][j] = array[i][j] + dp[i][j-1]


  print dp[m-1][n-1]

path = [[1, 2, 4],
        [2, 4, 1],
        [3, 2, 1]]
min_path_sum (path)
