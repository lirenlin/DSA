def getNext (array):
  count = 1
  prev = array[0]
  result = list ()
  if len (array) == 1:
    result.append (count)
    result.append (prev)
  else:
    for i in range (1, len (array)):
      if array[i] is prev:
        count = count + 1
      else:
        result.append (count)
        result.append (prev)
        count = 1
        prev = array[i]
      if i is len (array) - 1:
        result.append (count)
        result.append (prev)

  return result
      
def count_and_say (n):
  result = [1]
  for i in range (1, n):
    result = getNext (result)
  return result


print count_and_say (5)


