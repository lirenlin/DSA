#!/usr/bin/env python

l = ['a', 'b', 'c', 'a']
d = {}

for index in range(len(l)):
	item = l[index]
	if item not in d.keys():
		d[item] = index

print d
