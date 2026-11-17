#include "MiniMaxAi.h"
// what is miniman? its a algorithm where min and max are both trying to win, 
// min will always pic the worst move for max and max will pick the best foe itself.

//how minimax is working
//step1: get all available moves

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

int MiniMaxAi::EvaluationBoard(Board t_board)
{
	int score = 0;// collects the overall evaluation score for the board
	for (int row=0; row< t_board.GetRows(); row++)
	{
		for (int col = 0; col < t_board.GetCols(); col++) {
			if (col + 3 < t_board.GetCols()) // Check horizontal
			{
				score += EvaluateWindow(t_board, row, col, 0, 1);
			}
			if (row + 3 < t_board.GetRows()) // Check vertical
			{
				score += EvaluateWindow(t_board, row, col, 1, 0);
			}
			if (row + 3 < t_board.GetRows() && col + 3 < t_board.GetCols()) // Check diagonal down-right
			{
				score += EvaluateWindow(t_board, row, col, 1, 1);
			}
			if (row - 3 >= 0 && col + 3 < t_board.GetCols()) // Check diagonal up-right
			{
				score += EvaluateWindow(t_board, row, col, -1, 1);
			}
		}
	}
	return 0;
}

int MiniMaxAi::EvaluateWindow(Board t_board, int row, int col, int rowDir, int colDir)
{
	int myCount = 0;
	int opponentCount = 0;

	for (int i = 0; i < 4; i++)
	{
		char cell = t_board.GetCell(row + i * rowDir, col + i * colDir); // Get the cell value at the current position
		if (cell == m_myPiece)// Check if the cell contains the AI's piece
		{
			myCount++;// Increment the count of AI's pieces in the window
		}
		else if (cell == m_opponentPiece)// Check if the cell contains the opponent's piece
		{
			opponentCount++;// Increment the count of opponent's pieces in the window
		}
	}
	if (myCount > 0 && opponentCount > 0) // If both players have pieces in the window, it's not a good situation for either player
	{
		return 0;
	}
	if (myCount == 3) return 100;
	if (myCount == 2) return 10;
	if (myCount == 1) return 1;

	if (opponentCount == 3) return -100;
	if (opponentCount == 2) return -10;
	if (opponentCount == 1) return -1;

	return 0;
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
