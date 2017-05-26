pl = '.'
def valid_sudoku (grid):
    #row
    for i in range(9):
        row = list ()
        col = list ()
        box = list ()

        for j in range (9):
            #row
            item = grid[i][j]
            if item != pl:
                if item in row:
                    return False
                row.append (item)

            #column
            item = grid[j][i]
            if item != pl:
                if item in col:
                    return False
                col.append (item)

            #sub-box
            item = grid[i / 3 * 3 + j / 3][i % 3 * 3 + j % 3]
            if item != pl:
                if item in box:
                    return False
                box.append (item)
    return True

board = ["..9748...",
         "7........",
         ".2.1.9...",
         "..7...24.",
         ".64.1.59.",
         ".98...3..",
         "...8.3.2.",
         "........6",
         "...2759.."]
print valid_sudoku (board)

invalid_board =["..4...63.",
                ".........",
                "5......9.",
                "...56....",
                "4.3.....1",
                "...7.....",
                "...5.....",
                ".........",
                "........."]
print valid_sudoku (invalid_board)
