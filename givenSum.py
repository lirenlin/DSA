def solution_recursive (sum, n, start = 0):
  if sum <= 0 or n <= 0 or start > sum :
    return None
  if n == 1:
    return [[sum]]

  res = list ()
  for i in range (start, sum+1):
    ret = solution_recursive (sum - i, n - 1, i)
    if ret == None:
      continue

    for item in ret:
      item.insert (0, i)
    res.extend (ret)

  return res

print solution_recursive (5, 2)

result = list ()    
import copy
def solution_iterative (sum, n, start = 0, res = []):
  if sum == 0 and n == 0:
    result.append (res)
  elif n * sum == 0 and n != sum:
    return
  elif start > sum:
    return

  for i in range (start,sum+1):
    temp = copy.deepcopy (res)
    temp.append(i)
    solution_iterative (sum - i, n - 1, i, temp)


solution_iterative (5, 2)
print result
