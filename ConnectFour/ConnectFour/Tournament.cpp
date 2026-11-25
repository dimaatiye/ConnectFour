#include "Tournament.h"
#include <iostream>
#include <ctime>
#include "raylib.h"
#include "RandomAi.h"
#include <chrono>
#include <vector>
#include "MonteCarloAi.h"

struct GameResult
{
	char winner;
	int totalMoves;
	double redAiTotalMs; // Total time the red player Ai spent thinking
	int redAiMoves;
	double yellowAiTotalMs; // Total time the yellow player spent thinking
	int yellowAiMoves;
	bool illegalMove; // This should always be false unless theres something wrong with our algorithms!
};


GameResult PlayGame(AiPlayer* t_red, AiPlayer* t_yellow, int t_randomOpeningMoves)
{
	GameResult results = {};
	Board board;
	char currentPlayer = 'X';

	while (board.GetWinner() == ' ')
	{
		int column;

		if (board.GetMoveCount() < t_randomOpeningMoves)
		{
			std::vector<int> moves = board.GetValidMoves();
			column = moves[GetRandomValue(0, (int)moves.size() - 1)];
		}
		else
		{
			AiPlayer* currentAi = t_yellow;
			if (currentPlayer == 'X')
			{
				currentAi = t_red;
			}

			auto startTime = std::chrono::steady_clock::now();
			column = currentAi->ChooseMove(board);
			auto endTime = std::chrono::steady_clock::now();
			double ms = std::chrono::duration<double, std::milli>(endTime - startTime).count();

			if (currentPlayer == 'X')
			{
				results.redAiTotalMs += ms;
				results.redAiMoves++;
			}
			else
			{
				results.yellowAiTotalMs += ms;
				results.yellowAiMoves++;
			}
		}

		if (column < 0 || column >= board.GetCols() || board.IsColumnFull(column))
		{
			results.illegalMove = true;
			if (currentPlayer == 'X')
			{
				results.winner = 'O';
			}
			else
			{
				results.winner = 'X';
			}
			results.totalMoves = board.GetMoveCount();
			return results;
		}

		board.MakeMove(column, currentPlayer);

		if (currentPlayer == 'X')
		{
			currentPlayer = 'O';
		}
		else
		{
			currentPlayer = 'X';
		}
	}

	results.winner = board.GetWinner();
	results.totalMoves = board.GetMoveCount();
	return results;
}

void RunTournament()
{
	std::cout << "Tournament Mode\n";

	unsigned int seed = (unsigned int)time(nullptr);
	SetRandomSeed(seed);
	std::cout << "Random Seed: " << seed << "\n";

	MonteCarloAi redAi('X');
	redAi.SetDifficulty(100);
	RandomAi yellowAi('O');

	for (int game = 1; game <= 50; game++)
	{
		GameResult results = PlayGame(&redAi, &yellowAi, 2);

		double redAvgMs = 0;
		if (results.redAiMoves > 0)
		{
			redAvgMs = results.redAiTotalMs / results.redAiMoves;
		}

		std::cout << "Game: " << game
			<< ", Winner: " << results.winner
			<< ", Moves: " << results.totalMoves
			<< ", MCTS avg ms/move: " << redAvgMs
			<< ", Illegal: " << results.illegalMove << "\n";
	}
}