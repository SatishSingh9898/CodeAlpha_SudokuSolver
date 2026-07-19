#include <iostream>
using namespace std;

const int SIZE = 9;

// Function to print Sudoku
void printBoard(int board[SIZE][SIZE])
{
    cout << "\nSolved Sudoku:\n\n";

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if a number exists in the row
bool isRowSafe(int board[SIZE][SIZE], int row, int num)
{
    for (int col = 0; col < SIZE; col++)
    {
        if (board[row][col] == num)
            return false;
    }
    return true;
}

// Check if a number exists in the column
bool isColSafe(int board[SIZE][SIZE], int col, int num)
{
    for (int row = 0; row < SIZE; row++)
    {
        if (board[row][col] == num)
            return false;
    }
    return true;
}

// Check 3x3 subgrid
bool isBoxSafe(int board[SIZE][SIZE], int startRow, int startCol, int num)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[startRow + i][startCol + j] == num)
                return false;
        }
    }
    return true;
}

// Check whether it is safe to place a number
bool isSafe(int board[SIZE][SIZE], int row, int col, int num)
{
    return isRowSafe(board, row, num) &&
           isColSafe(board, col, num) &&
           isBoxSafe(board, row - row % 3, col - col % 3, num);
}

// Backtracking function
bool solveSudoku(int board[SIZE][SIZE])
{
    int row, col;
    bool empty = false;

    // Find an empty cell
    for (row = 0; row < SIZE; row++)
    {
        for (col = 0; col < SIZE; col++)
        {
            if (board[row][col] == 0)
            {
                empty = true;
                goto FOUND;
            }
        }
    }

FOUND:

    if (!empty)
        return true;

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(board, row, col, num))
        {
            board[row][col] = num;

            if (solveSudoku(board))
                return true;

            // Backtrack
            board[row][col] = 0;
        }
    }

    return false;
}

int main()
{
    int board[9][9] =
    {
        {3,0,6,5,0,8,4,0,0},
        {5,2,0,0,0,0,0,0,0},
        {0,8,7,0,0,0,0,3,1},
        {0,0,3,0,1,0,0,8,0},
        {9,0,0,8,6,3,0,0,5},
        {0,5,0,0,9,0,6,0,0},
        {1,3,0,0,0,0,2,5,0},
        {0,0,0,0,0,0,0,7,4},
        {0,0,5,2,0,6,3,0,0}
    };

    cout << "Original Sudoku:\n\n";

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    if (solveSudoku(board))
    {
        printBoard(board);
    }
    else
    {
        cout << "\nNo Solution Exists.";
    }

    return 0;
}