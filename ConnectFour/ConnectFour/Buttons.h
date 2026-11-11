#pragma once
#include "raylib.h"
class Buttons
{

private:
	Rectangle GetButtonRect(int index, int cols);
public:
	void DrawButton(int cols);
	int CheckButtonClick(int cols);
};

