#pragma once
#include "raylib.h"

const int MAX_SIZE = 7; // Max size a board can be in either dimension, switches when rotating the board

class Board
{

private:
	char m_grid[MAX_SIZE][MAX_SIZE];
	int m_rows;
	int m_cols;
	int m_moveCount;
	char m_winner;

public:
	Board();
	void DrawBoard();
	void PlacePiece(int column, char piece);
	bool IsColumnFull(int column);
	bool CheckWin(char piece);	
	void RotateClockwise();
	void ApplyGravityShift();
	void MakeMove(int col, char piece);
	bool IsBoardFull();

	int GetRows() { return m_rows; }
	int GetCols() { return m_cols; }
	int GetMoveCount() { return m_moveCount; }
	char GetWinner() { return m_winner; }

};

