#pragma once
#include "AiPlayer.h"

class MiniMaxAi : public AiPlayer
{
private:
	int m_maxDepth; // This is what difficulty will change
public:
	MiniMaxAi(char t_myPiece) : AiPlayer(t_myPiece)
	{
		// m_maxDepth = number
	}

	void SetDifficulty(int t_difficulty) override;

	int ChooseMove(Board t_board) override;
};

