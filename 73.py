def solution (array):
    m = len (array)
    n = len (array[0])
    line = list ()
    col = list ()

    for i in range (m):
        for j in range (n):
            if array[i][j] == 0:
                line.append (i)
                col.append (j)

    for i in line:
        for j in range (n):
            array[i][j] = 0

    for i in range (m):
        for j in col:
            array[i][j] = 0


matrix = [[1, 0, 1, 1],
          [1, 1, 0, 1],
          [1, 1, 1, 0],
          [1, 1, 1, 1]]
solution (matrix)
print matrix
