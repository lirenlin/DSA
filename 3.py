def solution (input):
  if len(input) == 0:
    return 0

  substr = dict ()
  max = 0
  start_ptr = 0
  end_ptr = 0

  for i in range (len (input)):
    char = input[i]
    end_ptr = i
    if char in substr:
      start_ptr = substr[char] + 1

      new_len = end_ptr - start_ptr + 1
      substr[char] = end_ptr
      if new_len > max:
	max = new_len
    else:
      substr[char] = i

  if end_ptr - start_ptr + 1 > max:
    max = end_ptr -start_ptr + 1
  return max


print solution ("abcde")
print solution ("abade")
print solution ("abaaa")
print solution ("aabac")
print solution ("aaaac")
print solution ("aaaaa")
