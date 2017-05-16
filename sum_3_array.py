
sum = 15
a = [0, 1, 2 ,3, 4, 5]
b = [6, 7, 1 ,2, 3, 4]

res1 = [sum - x for x in a]

b.sort ()

i = 0
j = len (a) - 1

while i < j:
    val = b[i] + b[j]
    if val in res1:
        print b[i], b[j], a[res1.index (val)]
        i = i + 1
    elif val > max (res1):
        j = j - 1
    elif val < min (res1):
        i = i + 1
    else:
        break


sum = 20
a = [0, 1, 12 ,13, 4, 5]
b = [6, 7, 1 ,2, 3, 4]
c = [1, 0, 3 ,5, 6, 10]

res1 = [sum - x for x in a]

b.sort ()
c.sort ()

for x in b:
    for y in c:
        tmp = x + y;
        if tmp > max (res1) or tmp < min (res1):
            exit ;
        if tmp in res1:
            print sum - x - y, x, y
