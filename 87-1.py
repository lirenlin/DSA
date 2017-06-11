from collections import defaultdict
def isScramble(s1, s2):
    if s1 == s2:
	return True
    count1 = defaultdict(int)
    count2 = defaultdict(int)
    for e1, e2 in zip(s1, s2):
	count1[e1] += 1
	count2[e2] += 1
    if count1 != count2:
	return False



    if len (s1) == 1:
	return s1 == s2
    elif len (s1) == 2:
	if s1[0] == s2[1] and s1[1] == s2[0]:
	    return True
	else:
	    return False

    for i in range (1, len (s1)):
	if isScramble (s1[:i], s2[:i]) and isScramble (s1[i:], s2[i:]) or isScramble (s1[-i:], s2[:i]) and isScramble (s1[:-i], s2[i:]):
	    return True

    return False


s1 = "rgtae"
s2 = "great"
print isScramble (s1, s2)
