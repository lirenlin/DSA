def solution (array):
  dict_list = dict ()
  for item in array:
    target = "".join (sorted (item))
    if target in dict_list:
      dict_list[target].append (item)
    else:
      dict_list[target] = [item]

  result = []
  for value in dict_list.values():
    result += [sorted(value)]

  print result

array = ["eat", "tea", "tan", "ate", "nat", "bat"]
solution (array)
