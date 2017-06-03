def solution (n, k):
  array = [i for i in range(1, n+1)]
  result = list ()
  factorial = 1
  k -= 1

  for i in range (1, n):
    factorial *= i

  while k >= 0:
    index = k // factorial
    result.append (array[index])
    array = array[:index] + array[index+1:]
    k %= factorial
    if not array:
      break
    factorial /= len (array)
  
  return result


print solution (3, 3)
print solution (4, 5)
print solution (4, 2)

