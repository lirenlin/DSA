def permutation (array):
    length = len (array)
    array.sort ()
    perm = list ()
    if length == 1:
        return [array]

    prev = -1
    for i in range (length):
        if prev == array[i]:
            continue
        prev = array[i]
        for sub in permutation (array[:i] + array[i+1:]):
            perm.append ([array[i]] + sub)

    return perm

array = [1, 2, 1]
print permutation (array)
print len (permutation (array))
