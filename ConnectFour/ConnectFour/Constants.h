#pragma once

// Window
const int SCREEN_WIDTH = 1900;
const int SCREEN_HEIGHT = 1300;

// Layout
const int CELL_SIZE = 150; // Width and Height of 1 cell in the board
const int BUTTON_TOP = 100; // Y pos of the buttons
const int BUTTON_HEIGHT = 50;
const int BOARD_TOP = 170; // Y pos of the top of the board



// Works out the X pos of the boards left edge so the board can be centered, takes cols as argument because board will be narrower after gravity shift
inline int GetBoardLeft(int cols)
{
	return (SCREEN_WIDTH - cols * CELL_SIZE) / 2;
}