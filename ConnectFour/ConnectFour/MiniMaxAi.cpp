#include "MiniMaxAi.h"

std::vector<int> MiniMaxAi::IsGamepadAvailableMoves(Board t_board)
{
	std::vector<int> availableMoves; // creates an empty list of moves
	for (int col = 0; col < t_board.GetCols(); col++) //gets the curerent number of cols
	{
		if (!t_board.IsColumnFull(col))// checks if the col is not full
		{
			availableMoves.push_back(col);//adds the avilable col to the bector
		}
	}
	return availableMoves;//return all available cols
}

void MiniMaxAi::SetDifficulty(int t_difficulty)
{
	m_maxDepth = t_difficulty;
}

int MiniMaxAi::ChooseMove(Board t_board)
{
	// This is where the MiniMax implementation will be
	return 0;
}
