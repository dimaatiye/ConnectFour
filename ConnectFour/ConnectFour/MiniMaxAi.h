#pragma once
#include "AiPlayer.h"
#include <vector>

class MiniMaxAi : public AiPlayer
{
private:
	int m_maxDepth; // This is what difficulty will change
	std::vector<int> GetAvailableMoves(Board t_board);
	int EvaluationBoard(Board t_board);// This will evaluate the board and return a score based on how good it is for the AI
	int EvaluateWindow(Board t_board, int row, int col, int rowDir, int colDir);// This will evaluate a window of 4 pieces and return a score based on how good it is for the AI
	int MiniMax(Board t_board, int t_depth, bool t_maxTurn);
public:
	MiniMaxAi(char t_myPiece) : AiPlayer(t_myPiece)
	{
		// m_maxDepth = number
	}

	void SetDifficulty(int t_difficulty) override;

	int ChooseMove(Board t_board) override;
};

