#pragma once
#include "AiPlayer.h"

class RandomAi : public AiPlayer
{
public:
	RandomAi(char t_myPiece) : AiPlayer(t_myPiece)
	{

	}

	void SetDifficulty(int t_difficulty) override
	{
		// This Ai picks moves at random so it doesnt need a difficulty
	}

	int ChooseMove(Board t_board) override
	{
		std::vector<int> moves = t_board.GetValidMoves();

		if (moves.empty())
		{
			return -1;
		}

		int randomIndex = GetRandomValue(0, (int)moves.size() - 1);
		return moves[randomIndex];
	}
};