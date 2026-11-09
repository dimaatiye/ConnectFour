#pragma once
#include "raylib.h"
class Buttons
{

private:
	Rectangle m_button[7];


public:
	Buttons();
	void DrawButton();
	int CheckButtonClick();
};

