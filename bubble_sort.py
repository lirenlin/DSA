#!/usr/bin/env python

import numpy as np
'''
bubble sort
O(N^2)
'''

array = np.random.randint (0, 100, size=10)

def bubble_sort (array):
    end = len (array)
    while end > 0:
        for index in range (end - 1):
            if array[index] > array[index+1]:
                tmp = array[index+1]
                array[index+1] = array[index]
                array[index] = tmp
        end = end - 1

    return array


print array
sorted_array = bubble_sort (array)
print sorted_array
