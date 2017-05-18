#!/usr/bin/env python
import numpy as np


'''
devide and conquer
O(nlogn)
'''

def merge_array (first, second):
    i = 0;
    j = 0;
    array = list ();
    while True:
        if i == len (first) and j == len (second):
            break
        if i == len (first):
            array.extend (second[j:])
            break
        if j == len (second):
            array.extend (first[i:])
            break

        if first[i] < second [j]:
            array.append (first[i])
            i = i + 1
        elif first[i] > second [j]:
            array.append (second[j])
            j = j + 1
        else:
            array.append (first[j])
            array.append (second[j])
            i = i + 1;
            j = j + 1;

    return array;

def merge_sort (array):
    if len (array) == 1:
        return array;

    half = len (array) / 2;
    first_array = merge_sort (array[:half])
    second_array = merge_sort (array[half:])

    return merge_array (first_array, second_array)


input = np.random.randint (0, 100, size = 10)
print input
sorted_array = merge_sort (input)
print sorted_array
