import sys
sys.setrecursionlimit (10000000)

pl = '.'
def valid_sudoku (grid, row, col):
    #row
    row_list = list ()
    col_list = list ()
    box_list = list ()
    for i in range(9):
        #row
        item = grid[row][i]
        if item != pl:
            if item in row_list:
                return False
            row_list.append (item)
        #column
        item = grid[i][col]
        if item != pl:
            if item in col_list:
                return False
            col_list.append (item)

        #sub-box
        item = grid[row/3*3 + i/3][col/3*3+i%3]
        if item != pl:
            if item in box_list:
                return False
            box_list.append (item)

    return True

def find_next_pos (grid, row, col):
    if grid[row][col] == pl:
        return (row, col)

    for i in range (row * 9 + col, 9 * 9):
            if grid[i/9][i%9] == pl:
                return (i/9, i%9)

    return (-1, -1)

def sudoku_try (grid, row, col):
    valid = False
    (row, col) = find_next_pos (grid, row, col)
    if row == -1:
        return True

    for i in range(1, 10):
        grid[row][col] = '%d' % i
        if not valid_sudoku (grid, row, col):
            continue

        if sudoku_try (grid, row, col):
            return True

    grid[row][col] = '.'
    return False


def sudoku_solver (grid):
    row = 0
    col = 0
    sudoku_try (grid, row, col)
    for line in grid:
        print line

board = ["..9748...",
         "7........",
         ".2.1.9...",
         "..7...24.",
         ".64.1.59.",
         ".98...3..",
         "...8.3.2.",
         "........6",
         "...2759.."]

board = [list(string) for string in board] 
sudoku_solver (board)
