
def fibonacci (n):
  '''DP with space optimization, only two data is stored
     a fibonacci serial looks like this: 0 1 1 2 3 5 8 ...
     the index start from 1 instead of 0
   '''
  if n < 1:
    print "invalid number %d " % (n)
  elif n == 1:
    return 0
  elif n == 2:
    return 1

  a = 0
  b = 1
  res = 0
  for i in range (2, n):
    res = a + b;
    a = b
    b = res 

  return res


print fibonacci (9)
