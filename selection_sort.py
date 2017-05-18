#!/usr/bin/env python

import numpy as np
'''
selection sort, in place sort with space complexity as O(1)
O(N^2)
'''

array = np.random.randint (0, 100, size=10)

def selection_sort (array):
    end = len (array)
    for index1 in range (end):
        for index2 in range (index1, end):
            if array[index1] > array[index2]:
                tmp = array[index1]
                array[index1] = array[index2]
                array[index2] = tmp

    return array


print array
sorted_array = selection_sort (array)
print sorted_array
