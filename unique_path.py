def unique_path (m, n):
  path = [[1 for __ in range (m)] for __ in range (n)]
  for i in range (1, n):
    for j in range (1, m):
      path[i][j] = path[i-1][j] + path[i][j-1]


  print path[n-1][m-1]


unique_path (3, 7)

def unique_path (m, n):
  m -= 1
  n -= 1
  n_factorial = 1
  m_factorial = 1
  nm_factorial = 1
  for i in range (1, n+1):
    n_factorial *= i
  for i in range (1, m+1):
    m_factorial *= i
  for i in range (1, n+m+1):
    nm_factorial *= i
  print nm_factorial / n_factorial / m_factorial

unique_path (3, 7)
