def minSubArrayLen (s, nums):
    length = len (nums)
    left, right = 0, 0
    min_start = 0
    min_end = 0
    min_len = length+1
    sum = 0

    while right < length:
        sum += nums[right]
        if sum == s:
            if min_len > right - left:
                min_len = right - left
                min_start = left
                min_end = right + 1
        elif sum > s:
            while left <= right:
                if sum - nums[left] == s:
                    sum -= nums[left]
                    left += 1
                    if min_len > right - left:
                        min_len = right - left
                        min_start = left
                        min_end = right + 1
                elif sum - nums[left] > s:
                    sum -= nums[left]
                    left +=1
                else:
                    break
        right += 1
    if min_len < length+1:
        return nums[min_start:min_end]
    else:
        return []

array = [1, 2, 3, 1, 1]
array1 = [1, 0, 3, 1, 1]

print minSubArrayLen (5, array)
print minSubArrayLen (5, array1)
print minSubArrayLen (6, array1)
print minSubArrayLen (7, array1)

