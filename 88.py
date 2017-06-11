def merge (nums1, m, nums2, n):
  ptr1 = m - 1
  ptr2 = n - 1
  index = m + n - 1
  while ptr1 >= 0 and ptr2 >= 0:
    if nums1[ptr1] > nums2[ptr2]:
      nums1[index] = nums1[ptr1]
      ptr1 -= 1
    else:
      nums1[index] = nums2[ptr1]
      ptr2 -= 1
    index -= 1

  if ptr1 < 0:
    nums1[:ptr2+1] = nums2[:ptr2+1]

num1 = [1, 1, 2, 2, 4, 0, 0, 0, 0]
num2 = [0, 0, 2, 3]

merge (num1, 5, num2, 4)
print num1
      
    
    
