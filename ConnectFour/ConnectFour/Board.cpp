#include "Board.h"
#include "Constants.h"

Board::Board()
{
    m_rows = 6;
    m_cols = 7;
    m_moveCount = 0;
    m_winner = ' ';

    // Clear the whole 7x7 grid even if only 6x7 or 7x6 is in use
    for (int row = 0; row < MAX_SIZE; row++)
    {
        for (int col = 0; col < MAX_SIZE; col++)
        {
            m_grid[row][col] = ' ';
        }
    }
}

void Board::DrawBoard()
{
    // Left edge will depend on the number of cols so the board can stay centered after a rotation
    int left = GetBoardLeft(m_cols);

    DrawRectangle(left, BOARD_TOP, m_cols * CELL_SIZE, m_rows * CELL_SIZE, BLUE);

    for (int row = 0; row < m_rows; row++)
    {
        for (int col = 0; col < m_cols; col++)
        {
            // To get cell center move along cell then add half a cell
            int x = left + col * CELL_SIZE + CELL_SIZE / 2;
            int y = BOARD_TOP + row * CELL_SIZE + CELL_SIZE / 2;
            float radius = CELL_SIZE / 2 - 12; // The -12 leaves a gap between spaces on the board

            if (m_grid[row][col] == 'X')
            {
                DrawCircle(x, y, radius, RED); // Draw player X's piece
            }
            else if (m_grid[row][col] == 'O')
            {
                DrawCircle(x, y, radius, YELLOW); // Draw player O's piece
            }
            else
            {
                DrawCircle(x, y, radius, BLACK); // Draw an empty space
            }
        }
    }
}

void Board::PlacePiece(int column, char piece)
{
    // Starts at the bottom row and moves up until an empty space is found
    for (int row = m_rows -1; row >= 0; row--)
    {
        if (m_grid[row][column] == ' ')// Check if the current position is empty
        {
            m_grid[row][column] = piece;// Place the player's piece in the empty position
            break;
        }
    }
}

bool Board::IsColumnFull(int column)
{
    if (m_grid[0][column] != ' ')
    {
        return true; // column is full
    }
	return false; // column is not full
}

bool Board::CheckWin(char piece)
{
    for (int row = 0; row < m_rows; row++)// check left to right
    {
        for (int col = 0; col < m_cols - 3; col++)
        {
            if (m_grid[row][col] == piece &&
                m_grid[row][col + 1] == piece &&
                m_grid[row][col + 2] == piece &&
                m_grid[row][col + 3] == piece)
            {
                return true;
            }
        }
    }
    for (int row = 0; row < m_rows - 3; row++)//check up to down
    {
        for (int col = 0; col < m_cols; col++)
        {
            if (m_grid[row][col] == piece &&
                m_grid[row + 1][col] == piece &&
                m_grid[row + 2][col] == piece &&
                m_grid[row + 3][col] == piece)
            {
                return true;
            }
        }
    }
    for (int row = 3; row < m_rows; row++)//diagnal down left to up right
    {
        for (int col = 0; col < m_cols - 3; col++)
        {
            if (m_grid[row][col] == piece &&
                m_grid[row - 1][col + 1] == piece &&
                m_grid[row - 2][col + 2] == piece &&
                m_grid[row - 3][col + 3] == piece)
            {
                return true;
            }
        }
    }
    for (int row = 0; row < m_rows - 3; row++)//diagnal down right to up left
    {
        for (int col = 0; col < m_cols - 3; col++)
        {
            if (m_grid[row][col] == piece &&
                m_grid[row + 1][col + 1] == piece &&
                m_grid[row + 2][col + 2] == piece &&
                m_grid[row + 3][col + 3] == piece)
            {
                return true;
            }
        }
    }

	return false;
}

void Board::RotateClockwise()
{
    // Copy the current board into temp and then clear it
    char temp[MAX_SIZE][MAX_SIZE];
    for (int row = 0; row < MAX_SIZE; row++)
    {
        for (int col = 0; col < MAX_SIZE; col++)
        {
            temp[row][col] = m_grid[row][col];
            m_grid[row][col] = ' ';
        }
    }

    // Swap the rows and cols, rows become cols, cols become rows
    int oldRows = m_rows;
    int oldCols = m_cols;
    m_rows = oldCols;
    m_cols = oldRows;

    // Fill in the new grid from the temp one
    for (int row = 0; row < m_rows; row++)
    {
        for (int col = 0; col < m_cols; col++)
        {
            m_grid[row][col] = temp[oldRows - 1 - col][row];
        }
    }
}

void Board::ApplyGravityShift()
{
    for (int col = 0; col < m_cols; col++)
    {
        // The next free spot for a piece to land, starts at the bottom 
        int writeRow = m_rows - 1; 
        // Check from bottom up so latest piece lands first and order is the same
        for (int row = m_rows - 1; row >= 0; row--)
        {
            if (m_grid[row][col] != ' ')
            {
                char piece = m_grid[row][col];
                m_grid[row][col] = ' ';
                m_grid[writeRow][col] = piece;
                writeRow--;
            }
        }
    }
}

void Board::MakeMove(int col, char piece)
{
    PlacePiece(col, piece);
    m_moveCount++;

    if (CheckWin(piece))
    {
        m_winner = piece;
        return;
    }
    // Rotate the board and apply gravity shift every 4th move
    if (m_moveCount % 4 == 0)
    {
        RotateClockwise();
        ApplyGravityShift();

        bool xWins = CheckWin('X');
        bool oWins = CheckWin('O');

        if (xWins && oWins)
        {
            m_winner = 'D'; // If the gravity shift causes both players to win at the same time, game is a draw
        }
        else if (xWins)
        {
            m_winner = 'X';
        }
        else if (oWins)
        {
            m_winner = 'O';
        }
    }
    // If no winner has been found and the board is full
    if (m_winner == ' ' && IsBoardFull())
    {
        m_winner = 'D';
    }
}

bool Board::IsBoardFull()
{
    for (int col = 0; col < m_cols; col++)
    {
        if (!IsColumnFull(col))
        {
            // If any col isnt full then the board cant be full
            return false; 
        }
    }
    return true; // Every col is full
}
