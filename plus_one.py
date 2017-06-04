def plus_one (array):
  carry = 1
  for i in range (len (array) -1 , -1, -1):
    val = array[i] + carry
    if val >= 10:
      carry = 1
      val -= 10
    else:
      carry = 0
    array[i] = val

    if i == 0 and carry == 1:
      array.insert (0, 1)
      
  return array

print plus_one([1, 2, 3, 4, 9])
print plus_one([9])
