import sys

def getMoneyAmount (N):
  # number of guess
  dp_dict = dict ()
  dp = [-1 for i in range (N+1)]

  dp[0] = 0
  dp_dict [0] = 0
  dp[1] = 0
  dp_dict [1] = 0
  dp[2] = 1
  dp_dict [2] = 1
  dp[3] = 2
  dp_dict [3] = 1
  dp[4] = 4
  dp_dict [4] = 2

  for i in range (4, N+1):
    # i - 3 is the split point
    val_left = dp[i-4] + i - 3
    val_right = i - 3 + i - 1
    num = 0
    val = 0
    if val_left > val_right:
      val = val_left
      num = dp_dict[i-4]+1
    else:
      val = val_right
      num = 2

    for j in range (i-4, 4, -1):
      # j is the split point
      val_left = dp[j-1] + j
      val_right = dp[i-j+1] + dp_dict[i-j+1] * (j - 1)
      if val_left > val_right:
        new_val = val_left
        n = dp_dict[j-1]+1
      else:
        new_val = val_right
        n = dp_dict[i-j]
      if new_val > val:
        val = new_val
        num = n

    dp[i] = val
    dp_dict[i] = num
    print i, dp[i]

  return dp[N]


while True:
  n= input ("give N: ")
  getMoneyAmount (int (n))
