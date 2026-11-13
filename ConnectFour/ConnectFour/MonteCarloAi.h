#pragma once
#include "AiPlayer.h"

class MonteCarloAi: public AiPlayer
{
private:
	int m_iterations; // This is what difficulty will change
public:
	MonteCarloAi(char t_myPiece) : AiPlayer(t_myPiece)
	{
		// m_iterations = number
	}

	void SetDifficulty(int t_difficulty) override;
	int ChooseMove(Board t_board) override;
};

