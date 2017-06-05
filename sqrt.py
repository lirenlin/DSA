#Newton's method
def sqrt (val):
    init = 10.0
    delta = 0.1
    while abs (init * init - val) > delta:
        init = (init + val / init) / 2

    return int (init)

print sqrt (5)
print sqrt (4)
print sqrt (9)
