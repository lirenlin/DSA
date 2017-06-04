def binary_add (a, b):
  carry = 0
  result = ""
  add = None

  if len (a) > len (b):
    add1 = "0" * (len (a) - len (b)) + b
    add2 = a
  else:
    add1 = "0" * (len (b) - len (a)) + a
    add2 = b

  for i in range (len (add1) - 1, -1, -1):
    val = int (add1[i]) + int (add2[i]) + carry
    if val == 2:
      carry = 1
      result = str (0) + result
    else:
      carry = 0
      result = str (val) + result

    if i == 0 and carry == 1:
      result = "1" + result

  return result

print binary_add ("101", "1")
