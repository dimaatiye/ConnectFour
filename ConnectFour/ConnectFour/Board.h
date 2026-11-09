#pragma once
#include "raylib.h"
class Board
{

private:
	char m_grid[6][7];

public:
	Board();
	void DrawBoard();
	void PlacePiece(int column, char piece);
	bool IsColumnFull(int column);
	bool CheckWin(char piece);	

};

