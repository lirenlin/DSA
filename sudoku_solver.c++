#include <iostream>
#include <vector>
using namespace std;

typedef vector <vector <char>> Board;
class Solution
{
public:
  void solveSudoku (Board &board);

private:
  bool validP (unsigned row, unsigned col, Board &board);
  bool solveSudoku (Board &board, int i, int j);
};

void Solution::solveSudoku (Board &board)
{
  solveSudoku (board, 0, 0);
}

bool Solution::solveSudoku (Board &board, int row, int col)
{
  if (row == 9)
      return true;

  int next_row = 0;
  int next_col = 0;
  if (col == 8)
    {
      next_row = row + 1;
      next_col = 0;
    }
  else
    {
      next_row = row;
      next_col = col + 1;
    }

  if (board[row][col] != '.')
    {
      if (!validP (row, col, board))
	return false;
      return solveSudoku (board, next_row, next_col);
    }

  for (unsigned val = 0; val < 9; ++val)
    {
      board[row][col] = val + '1';
      if (validP (row, col, board) && solveSudoku (board, next_row, next_col))
	return true;
    }
  board[row][col] = '.';
  return false;
}

bool Solution::validP (unsigned row, unsigned col, Board &board)
{
  unsigned start_row = row / 3 * 3;
  unsigned start_col = col / 3 * 3;
  unsigned val = board[row][col];

  int bitMap = 0;
  for (unsigned i = start_row; i < start_row + 3; i++)
    for (unsigned j = start_col; j < start_col + 3; j++)
      {
	if (val == board[i][j] && (i != row || j != col))
	  return false;
      }

  for (unsigned i = 0; i < 9; ++i)
    {
      if (val == board[i][col] && i != row)
	return false;
      if (val == board[row][i] && i != col)
	return false;
    }

  return true;
}

int main ()
{
  Board board;

  vector<char> row0 {'.','.','9','7','4','8','.','.','.'};
  vector<char> row1 {'7','.','.','.','.','.','.','.','.'};
  vector<char> row2 {'.','2','.','1','.','9','.','.','.'};
  vector<char> row3 {'.','.','7','.','.','.','2','4','.'};
  vector<char> row4 {'.','6','4','.','1','.','5','9','.'};
  vector<char> row5 {'.','9','8','.','.','.','3','.','.'};
  vector<char> row6 {'.','.','.','8','.','3','.','2','.'};
  vector<char> row7 {'.','.','.','.','.','.','.','.','6'};
  vector<char> row8 {'.','.','.','2','7','5','9','.','.'};

  board.push_back (row0);
  board.push_back (row1);
  board.push_back (row2);
  board.push_back (row3);
  board.push_back (row4);
  board.push_back (row5);
  board.push_back (row6);
  board.push_back (row7);
  board.push_back (row8);

  Solution solution;
  solution.solveSudoku (board);
  for (auto row : board)
    {
      for (auto val : row)
	cout << val << ' ';
      cout << endl;
    }

  return 0;
}
