#include "Buttons.h"

Buttons::Buttons()
{
	for(int i = 0; i < 7; i++)
	{
		m_button[i] = { 100.0f + i * 250, 100, 200, 50 };
	}
}

void Buttons::DrawButton()
{
	for (int i = 0; i < 7; i++)
	{
		DrawRectangleRec(m_button[i], BLACK);
		DrawText("Press", static_cast<int>(m_button[i].x) + 50, static_cast<int>(m_button[i].y) + 15, 20, WHITE);
	}
}
