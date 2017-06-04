def assign_space (array, line_len):
  result = ""
  for item in array:
    result += item
    
  return result

def text_justification (array, line_len):
  result = list ()
  new_line = False
  first_ptr = 0

  while first_ptr < len (array):
    length = len (array[first_ptr])
    for second_ptr in range (first_ptr + 1, len (array)):
      length += len (array[second_ptr]) + 1 # a space
      if length > line_len:
	val = assign_space (array [first_ptr : second_ptr], line_len)
	result.append (val)
	first_ptr = second_ptr
	length = 0
	break
    if first_ptr == len (array) - 1:
      result.append (array[first_ptr])
      break

  return result

words = ["This", "is", "an", "example", "of", "text", "justification."]
print text_justification (words, 16)
