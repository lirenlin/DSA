def solution (array):
  max_sum = 0
  max_path = list ()
  curr_sum = 0
  curr_path = list ()

  for num in array:
    if curr_sum < 0:
      curr_sum = 0
      curr_path = list ()

    curr_sum += num
    curr_path.append (num)

    if max_sum < curr_sum:
      max_sum = curr_sum 
      # deep copy here
      max_path = curr_path[:]
    
  print max_sum, max_path


nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
solution (nums)
