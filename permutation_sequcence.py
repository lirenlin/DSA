def solution (n, k):
  array = [i for i in range(1, n+1)]
  result = list ()
  factorial = 1

  for i in range (1, n):
    factorial *= i

  while k >= 1:
    index = k // factorial
    print index
    print array
    result.append (array[index])
    array = array[:index] + array[index+1:]
    k %= factorial
    factorial /= len (array)
  
  print result 


print solution (3, 3)
#print solution (4, 5)

