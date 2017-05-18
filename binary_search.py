#!/usr/bin/env python

import numpy as np
'''
divide and conquer, sorted array
O(logN)
'''
array = np.random.randint (0, 100, size=10)
array.sort ()

def binary_search (array, key):
    hi_index = len (array) - 1
    lo_index = 0
    while hi_index > lo_index:
        mid = (hi_index + lo_index) / 2
        if array[mid] == key:
            print "found at %d" % (mid)
            break
        elif key < array[mid]:
            hi_index = mid
        elif key > array[mid]:
            lo_index = mid

binary_search (array, array[5])
