#!/usr/bin/env python

import numpy as np
'''
shortest subarray with sum greater than given number
O(N)
'''

#array = np.random.randint (0, 10, size=10)
array = [1, 9, 0, 1, 10, 5]
limit = 10

def smallestSubWithSum (array, limit):
    step = list ();
    sum = 0
    start = 0
    end = len (array) - 1
    for i in range(len (array)):
        sum = sum + array[i]
        if sum >= limit:
            while sum > limit and start < i:
                sum = sum - array[start]
                start = start + 1

    return (start, end)


print array, limit
print smallestSubWithSum (array, limit)
