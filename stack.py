#!/usr/bin/env python

class Stack (object):
	def __init__(self):	
		self.index = 0
		self.size = 0
		self.list = list ()

	def pop (self):
		if self.index == 0:
			return None
		else:
			self.index = self.index - 1
			item = self.list[self.index]
			return item

	def push (self, item):
		self.list.append(item)
		self.index = self.index + 1

	def __str__ (self):
		str = "["
		for i in range (0,self.index):
			str = "%s%d" % (str, self.list[i])
		str = str +"]"
		return str


stack = Stack ()
stack.push (10)
stack.push (11)
print stack
stack.pop ()
print stack
