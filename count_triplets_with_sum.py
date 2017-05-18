#!/usr/bin/env python

import numpy as np
'''
insertion sort, in place sort, space complexity O(1)
O(N^2)
'''

array = np.random.randint (0, 10, size=10)
limit = 12

def find_triple (array):
    array.sort ()
    print array
    res_list = list ()
    for index in range (len (array)-2):
        for index1 in range(index+2,len (array)):
            sum = array[index] + array[index+1] + array[index1]
            if sum <= limit:
                res_list.append ((array[index], array[index+1], array[index1]))
            else:
                break

    return res_list


print array
res = find_triple (array)
print res, "sum smaller than %d" %(limit)
