from collections import defaultdict

def solution (s, t):
    found = False
    first_ptr, second_ptr = 0, 0
    min_start, min_end = 0, len (s) - 1
    char_need = defaultdict(int)

    for i in t:
        char_need[i] += 1
    len_need = len (t)

    while second_ptr < len (s):
        if char_need[s[second_ptr]] > 0:
            len_need -= 1

        char_need[s[second_ptr]] -= 1

        while len_need == 0:
            found = True
            if min_end - min_start > second_ptr - first_ptr:
                min_start = first_ptr
                min_end = second_ptr

            char_need[s[first_ptr]] += 1

            if char_need[s[first_ptr]] > 0:
                len_need += 1
            first_ptr += 1

        second_ptr += 1

    return s[min_start:min_end+1] if found else ""

print solution ("ADOBECODEBANC", "ABC")
print solution ("A", "AC")
print solution ("a", "aa")
print solution ("ab", "a")
