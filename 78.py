def solution1 (nums):
    if len (nums) == 1:
        return [[], nums]

    res = solution1 (nums[1:])
    for i in solution1 (nums[1:]):
        res.append (i + [nums[0]])

    return res

def solution2 (nums):
    res = [[]]
    for num in nums:
        res += [item + [num] for item in res]
    return res

print solution1 ([1,2,3])
print solution2 ([1,2,3])
