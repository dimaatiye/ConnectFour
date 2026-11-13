#include "Menu.h"
#include "Constants.h"
#include "MiniMaxAi.h"
#include "MonteCarloAi.h"

Menu::Menu()
{
	Reset();
}

void Menu::Reset()
{
	m_screen = 0;
	m_gameMode = TWO_PLAYERS;
	m_difficulty = EASY;
	m_aiType = MINIMAX;
}

bool Menu::DrawMenuButton(const char* t_text, int t_x, int t_y)
{
	Rectangle rect;
	rect.x = (float)t_x;
	rect.y = (float)t_y;
	rect.width = 600;
	rect.height = 90;

	bool hovered = CheckCollisionPointRec(GetMousePosition(), rect);

	if (hovered)
	{
		DrawRectangleRec(rect, YELLOW);
	}
	else
	{
		DrawRectangleRec(rect, WHITE);
	}

	int textWidth = MeasureText(t_text, 40);
	DrawText(t_text, t_x + (600 - textWidth) / 2, t_y + 25, 40, BLACK);

	return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Menu::UpdateAndDraw()
{
	const char* title = "Gravity Shift Connect 4";
	DrawText(title, (SCREEN_WIDTH - MeasureText(title, 80)) / 2, 150, 80, WHITE);

	if (m_screen == 0)
	{
		const char* heading = "Choose a game mode";
		DrawText(heading, (SCREEN_WIDTH - MeasureText(heading, 50)) / 2, 330, 50, RED);

		if (DrawMenuButton("2 Players", 650, 450))
		{
			m_gameMode = TWO_PLAYERS;
			m_screen = 3; 
		}
		if (DrawMenuButton("1 Player vs AI", 650, 570))
		{
			m_gameMode = PLAYER_VS_AI;
			m_screen = 1;
		}
		if (DrawMenuButton("AI vs AI", 650, 690))
		{
			m_gameMode = AI_VS_AI;
			m_screen = 1;
		}
	}
	else if (m_screen == 1)
	{
		const char* heading = "Choose AI difficulty";
		DrawText(heading, (SCREEN_WIDTH - MeasureText(heading, 50)) / 2, 330, 50, RED);

		if (DrawMenuButton("Easy", 650, 450))
		{
			m_difficulty = EASY;
			m_screen = 2;
		}
		if (DrawMenuButton("Hard", 650, 570))
		{
			m_difficulty = HARD;
			m_screen = 2;
		}
		if (DrawMenuButton("Back", 650, 690))
		{
			m_screen = 0;
		}
	}
	else if (m_screen == 2)
	{
		const char* heading = "Choose AI algorithm";
		DrawText(heading, (SCREEN_WIDTH - MeasureText(heading, 50)) / 2, 330, 50, RED);

		if (DrawMenuButton("Minimax", 650, 450))
		{
			m_aiType = MINIMAX;
			m_screen = 3;
		}
		if (DrawMenuButton("Monte Carlo", 650, 570))
		{
			m_aiType = MONTE_CARLO;
			m_screen = 3;
		}
		if (DrawMenuButton("Back", 650, 690))
		{
			m_screen = 1;
		}
	}
}

AiPlayer* Menu::CreateAi(char t_piece)
{
	AiPlayer* ai;

	if (m_aiType == MINIMAX)
	{
		ai = new MiniMaxAi(t_piece);

		if (m_difficulty == EASY)
		{
			ai->SetDifficulty(2); 
		}
		else
		{
			ai->SetDifficulty(4); 
		}
	}
	else
	{
		ai = new MonteCarloAi(t_piece);

		if (m_difficulty == EASY)
		{
			ai->SetDifficulty(3); 
		}
		else
		{
			ai->SetDifficulty(5); 
		}
	}

	return ai;
}