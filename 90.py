def subsetsWithDup (nums):
    result = [[]]
    nums.sort ()
    size = 0

    for i in range (len (nums)):
        start =  size if i >= 1 and nums[i] == nums[i-1] else 0
        size = len (result)
        for j in range (start, size):
            result.append (result[j] + [nums[i]])
    return result

print subsetsWithDup ([1,2,2])
