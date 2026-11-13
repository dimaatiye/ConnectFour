#pragma once
#include "raylib.h"
#include "AiPlayer.h"

// Game modes
const int TWO_PLAYERS = 0;
const int PLAYER_VS_AI = 1;
const int AI_VS_AI = 2;

// Difficulties
const int EASY = 0;
const int HARD = 1;

// AI types
const int MINIMAX = 0;
const int MONTE_CARLO = 1;

class Menu
{
private:
	int m_screen;  // 0 = pick game mode, 1 = pick difficulty, 2 = pick AI type, 3 = menu is finished
	int m_gameMode;   // TWO_PLAYERS, PLAYER_VS_AI or AI_VS_AI
	int m_difficulty; // EASY or HARD
	int m_aiType;     // MINIMAX or MONTE_CARLO

	bool DrawMenuButton(const char* t_text, int t_x, int t_y); 

public:
	Menu();
	void Reset();         
	void UpdateAndDraw(); 

	bool IsFinished() { return m_screen == 3; }
	int GetGameMode() { return m_gameMode; }

	AiPlayer* CreateAi(char t_piece); 
};