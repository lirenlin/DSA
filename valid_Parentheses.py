def is_valid (string):
    if len (string) % 2 == 1:
        return False

    stack = list ()
    left = ("(", "{", "[")
    right = (")", "}", "]")

    for c in string:
        if c in left:
            stack.append (c)
        else:
            prev = stack.pop ()
            if left.index (prev) != right.index (c):
                return False

    return len (stack) == 0

print is_valid ("{}[]()")
print is_valid ("{[]}()")
print is_valid ("{[()]}")
print is_valid ("{[(})]")
