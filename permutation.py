def permutation (array):
    length = len (array)
    perm = list ()
    if length == 1:
        return [array]

    for i in range (length):
        for sub in permutation (array[:i] + array[i+1:]):
            perm.append ([array[i]] + sub)

    return perm


array = [1]
print permutation (array)
print len (permutation (array))
