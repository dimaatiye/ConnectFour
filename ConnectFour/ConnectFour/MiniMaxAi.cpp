#include "MiniMaxAi.h"
#include <limits>
#include <algorithm>
#include <iostream>
// what is miniman? its a algorithm where min and max are both trying to win, 
// min will always pic the worst move for max and max will pick the best foe itself.

//how minimax is working
//step1: get all available moves

std::vector<int> MiniMaxAi::GetAvailableMoves(Board t_board)
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
	return score;
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

int MiniMaxAi::MiniMax(Board t_board, int t_depth, bool t_maxTurn, int alpha, int beta) //depth is how far we have searched
{
	if (t_board.CheckWin(m_myPiece)) // Check if the AI has won
	{
		return 100000; // Return a high score for a win
	}
	if (t_board.CheckWin(m_opponentPiece)) // Check if the opponent has won
	{
		return -100000; // Return a low score for a loss
	}
	if (t_board.IsBoardFull())
	{
		return 0;
	}
	if (t_depth == m_maxDepth) // Check if the maximum depth has been reached
	{
		return EvaluationBoard(t_board); // Evaluate the board and return the score
	}

	std::vector<int> availableMoves = GetAvailableMoves(t_board);

	if (t_maxTurn)//explore possible moves, trus is maxs turn
	{
		int bestScore = std::numeric_limits<int>::min();//returns the tiniest value, so ai can find something better
		for (int move : availableMoves)//loop through avainlabe moves
		{
			Board copyBoard = t_board;//create a copey of the board
			copyBoard.MakeMove(move, m_myPiece);// place the ai piece
			int score = MiniMax(copyBoard, t_depth + 1, false, alpha, beta);
			bestScore = std::max(bestScore, score);// the highest scre we found so far
			alpha = std::max(alpha, bestScore);//update alhpa every time we find a better score for max
			if (beta <= alpha)//if beta is less than or equal to alpha, we can stop searching this branch
			{
				break; // Beta cut-off
			}
		}
		return bestScore;
	}
	int bestScore = std::numeric_limits<int>::max();
	for (int move : availableMoves)
	{
		Board childBoard = t_board;
		childBoard.MakeMove(move, m_opponentPiece);
		int score = MiniMax(childBoard, t_depth + 1, true, alpha, beta);
		bestScore = std::min(bestScore, score);
		beta = std::min(beta, bestScore);
		if (beta <= alpha)
		{
			break;
		}
	}
	return bestScore;
}

void MiniMaxAi::SetDifficulty(int t_difficulty)
{
	if (t_difficulty == 1)
	{
		m_maxDepth = 2;
	}
	else if(t_difficulty == 2)
	{
		m_maxDepth = 4;
	}
	else if (t_difficulty == 3)
	{
		m_maxDepth = 6;
	}
	else
	{
		m_maxDepth = 2;
	}
}

int MiniMaxAi::ChooseMove(Board t_board)
{
	// This is where the MiniMax implementation will be
	//1 get available moves
	std::vector<int> availableMoves = GetAvailableMoves(t_board);
	//2inisilaise bestscore and bestmove
	int bestScore = std::numeric_limits<int>::min();
	int bestMove = -1;
	//3 loop through all available moves 
	for (int move : availableMoves)
	{
		//Creates a copy of the current board
		Board copyBoard = t_board;
		//Places the AI's piece (O) in the column we're currently testing.
		copyBoard.MakeMove(move, m_myPiece);
		//starts the Minimax search at depth 0 because we're beginning a new search for this particular move
		int score = MiniMax(copyBoard, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());//aplha starts the lowest possible, beta starts the highest possible
		std::cout << "Column: " << move << " Score: " << score << std::endl;
		//Checks if the current move has a higher score than the best score we've found.
		if (score > bestScore)
		{
			bestScore = score;
			bestMove = move;
		}

	}
	return bestMove;
}
