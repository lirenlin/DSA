def solution (nums):
    red_ptr = 0
    blue_ptr = len (nums) - 1
    i = 0

    while i <= blue_ptr:
        if nums[i] == 0: #red
            nums[i] = nums[red_ptr]
            nums[red_ptr] = 0
            red_ptr += 1
            i += 1
        elif nums[i] == 2: #blue
            nums[i] = nums[blue_ptr]
            nums[blue_ptr] = 2
            blue_ptr -= 1
        else: #next
            i += 1

l = [1, 2, 1, 2, 0, 2, 1, 0, 2, 0, 0, 2]
solution (l)
print l

l = [1, 0]
solution (l)
print l

l = [0]
solution (l)
print l


