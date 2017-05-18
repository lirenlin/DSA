#!/usr/bin/env python

import numpy as np
'''
brute force, not require the array is sorted.
O(N)
'''
#!/usr/bin/env python

import numpy as np
'''
brute force
not require the array is already sorted
O(logN)
'''
array = np.random.randint (0, 100, size=10)
array.sort ()

def linear_search (array, key):
    for index in range (len (array)):
        if array[index] == key:
            print index

key = array[5]
print "find %d in array: " % (key), array
linear_search (array, key)
