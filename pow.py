def solution (val, N):
  if N == 0:
    return 1
  elif N == 1:
    return val

  result = val
  n = N
  if n % 2 != 0:
    n = N + 1

  while n != 1: 
    if n % 2 == 0:
      result *= result
      n = n >> 1
      if n == 1:
	break
    else:
      result *= val
      n -= 1

  if N % 2 != 0:
    result /= val

  return result


print solution (2, 1)
print solution (2, 2)
print solution (2, 3)
print solution (2, 4)
print solution (2, 5)



