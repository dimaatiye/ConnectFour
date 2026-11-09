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
            DrawCircle(200 + (col * 250),250 + (row * 180),75,WHITE);

            DrawCircle(200 + (col * 250),250 + (row * 180),65,BLACK);
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
	return false;
}

bool Board::CheckWin(char piece)
{
	return false;
}
