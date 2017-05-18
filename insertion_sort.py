#!/usr/bin/env python

import numpy as np
'''
insertion sort, in place sort, space complexity O(1)
O(N^2)
'''

array = np.random.randint (0, 100, size=10)

def insertion_sort (array):
    for index in range (len (array)-1):
        if array[index] > array[index+1]:
            tmp = array[index];
            array[index] = array[index+1]
            array[index+1] = tmp
            for index in reversed (range (1, index)):
                if array[index] < array[index - 1]:
                    tmp = array[index-1];
                    array[index-1] = array[index]
                    array[index] = tmp

    return array


print array
sorted_array = insertion_sort (array)
print sorted_array
