#include "Board.h"

Board::Board()
{
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            m_grid[row][col] = ' ';
        }
    }
}

void Board::DrawBoard()
{
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {

			int x = 200 + (col * 250);
			int y = 250 + (row * 180);
            DrawCircle(x, y, 75, WHITE);

            if (m_grid[row][col] == 'X')
            {
                DrawCircle(x, y, 65, RED); // Draw player X's piece
            }
            else if (m_grid[row][col] == 'O')
            {
                DrawCircle(x, y, 65, YELLOW); // Draw player O's piece
            }
            else
            {
                DrawCircle(x, y, 65, BLACK); // Draw an empty space
            }
        }
    }
}

void Board::PlacePiece(int column, char piece)
{
    for (int row = 5; row >= 0; row--)
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
    for (int row = 0; row < 6; row++)// check left to right
    {
        for (int col = 0; col < 4; col++)
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
	return false;
}
