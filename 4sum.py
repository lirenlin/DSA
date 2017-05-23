def fourSum (array, target):
    result = set ()
    twoSumIndex = {}
    for i in range (len (array)):
        for j in range (i + 1, len (array)):
            twoSum = array[i] + array[j]
            if twoSum in twoSumIndex:
                twoSumIndex[twoSum].append ((i, j))
            else:
                twoSumIndex[twoSum] = [(i, j)]

    for i in range (len (array)):
        for j in range (i + 1, len(array)):
            res = target - array[i] - array[j]
            if res in twoSumIndex:
                for item in twoSumIndex[res]:
                    if i not in item and j not in item:
                        result.add (tuple (sorted ([array[i], array[j],
                            array[item[0]], array[item[1]]])))

    return result

def fourSum_2 (array, target):
    result = set ()
    twoSumIndex = {}
    for i in range (len (array)):
        for j in range (i + 1, len (array)):
            twoSum = array[i] + array[j]
            if twoSum in twoSumIndex:
                twoSumIndex[twoSum].append ((i, j))
            else:
                twoSumIndex[twoSum] = [(i, j)]

    for val, index in twoSumIndex.items ():
        res = target - val
        if res in twoSumIndex:
            for item1 in twoSumIndex[res]:
                for item2 in index:
                  if item1[0] not in item2 and item1[1] not in item2:
                      result.add (tuple (sorted ([array[item1[0]],
                        array[item1[1]], array[item2[0]], array[item2[1]]])))

    return result

array = [1, 0, -1, 0, -2, 2]
target = 0
print fourSum (array, target)

print fourSum_2 (array, target)

