#include "Tournament.h"
#include <iostream>
#include <ctime>
#include "raylib.h"
#include "RandomAi.h"
#include <chrono>
#include <vector>
#include "MonteCarloAi.h"
#include "MiniMaxAi.h"
#include <string>
#include <cmath>
#include <fstream>

const int AI_RANDOM = 0;
const int AI_MINIMAX = 1;
const int AI_MCTS = 2;

AiPlayer* CreateAi(int t_type, int t_setting, char t_piece)
{
	AiPlayer* ai;

	if (t_type == AI_MINIMAX)
	{
		ai = new MiniMaxAi(t_piece);
	}
	else if (t_type == AI_MCTS)
	{
		ai = new MonteCarloAi(t_piece);
	}
	else
	{
		ai = new RandomAi(t_piece);
	}

	ai->SetDifficulty(t_setting);
	return ai;
}

const char* GetAiName(int t_type)
{
	if (t_type == AI_MINIMAX)
	{
		return "Minimax";
	}
	else if (t_type == AI_MCTS)
	{
		return "MCTS";
	}
	return "Random";
}

struct GameResult
{
	char winner;
	int totalMoves;
	double redAiTotalMs; // Total time the red player Ai spent thinking
	int redAiMoves; // Total Moves made by Red
	double yellowAiTotalMs; // Total time the yellow player spent thinking
	int yellowAiMoves; // Total moves made by Yellow
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
			// Start the clock
			auto startTime = std::chrono::steady_clock::now();
			column = currentAi->ChooseMove(board);
			// Stop the clock
			auto endTime = std::chrono::steady_clock::now();
			// Note the time taken
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

		// All going well this never runs, but if it does, the Ai that made the illegal move loses 
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

void RunMatch(std::string t_name, int t_typeA, int t_settingA, int t_typeB, int t_settingB, int t_numOfGames, int t_randomOpeningMoves, std::ofstream& t_csv)
{
	AiPlayer* aAsRed = CreateAi(t_typeA, t_settingA, 'X');
	AiPlayer* aAsYellow = CreateAi(t_typeA, t_settingA, 'O');
	AiPlayer* bAsRed = CreateAi(t_typeB, t_settingB, 'X');
	AiPlayer* bAsYellow = CreateAi(t_typeB, t_settingB, 'O');

	int aWins = 0; 
	int bWins = 0;
	int draws = 0;

	std::cout << "\n" << t_name << ": " << GetAiName(t_typeA) << " " << t_settingA << " vs " << GetAiName(t_typeB) << " " << t_settingB << " (" << t_numOfGames << " games)\n";

	for (int game = 0; game < t_numOfGames; game++)
	{
		bool aIsRed = (game % 2 == 0);

		GameResult results;

		if (aIsRed)
		{
			results = PlayGame(aAsRed, bAsYellow, t_randomOpeningMoves);
		}
		else
		{
			results = PlayGame(bAsRed, aAsYellow, t_randomOpeningMoves);
		}

		char aPiece = 'O';
		if (aIsRed)
		{
			aPiece = 'X';
		}

		// Count results from A's POV, 1 = win, 0.5 = draw, 0 = loss
		double scoreForA;

		if (results.winner == 'D')
		{
			scoreForA = 0.5;
			draws++;
		}
		else if (results.winner == aPiece)
		{
			scoreForA = 1.0;
			aWins++;
		}
		else
		{
			scoreForA = 0.0;
			bWins++;
		}

		double redAvgMs = 0;
		if (results.redAiMoves > 0)
		{
			redAvgMs = results.redAiTotalMs / results.redAiMoves;
		}

		double yellowAvgMs = 0;
		if (results.yellowAiMoves > 0)
		{
			yellowAvgMs = results.yellowAiTotalMs / results.yellowAiMoves;
		}

		std::string aColour = "Yellow";
		if (aIsRed)
		{
			aColour = "Red";
		}

		std::string illegal = "no";
		if (results.illegalMove)
		{
			illegal = "yes";
		}

		// Write one row for this game same order as the header is crucial!
		t_csv << t_name << ","
			<< game + 1 << ","
			<< GetAiName(t_typeA) << "," << t_settingA << ","
			<< GetAiName(t_typeB) << "," << t_settingB << ","
			<< aColour << ","
			<< results.winner << ","
			<< scoreForA << ","
			<< results.totalMoves << ","
			<< redAvgMs << ","
			<< yellowAvgMs << ","
			<< illegal << "\n";

		if ((game + 1) % 10 == 0)
		{
			std::cout << "  " << game + 1 << "/" << t_numOfGames << " games played\r" << std::flush;
		}
	}
	std::cout << "\n";

	double score = (aWins + 0.5 * draws) / t_numOfGames;
	double margin = 1.96 * std::sqrt(score * (1.0 - score) / t_numOfGames);

	std::cout << "  A wins: " << aWins << "  B wins: " << bWins << "  Draws: " << draws << "\n";
	std::cout << "  Score for A: " << score * 100 << "% (+/- " << margin * 100 << "%)\n";

	delete aAsRed;
	delete aAsYellow;
	delete bAsRed;
	delete bAsYellow;
}

void RunTournament()
{
	std::cout << "Tournament Mode\n";

	// The main game sets its own random seed but we need another one here because the tournament doesnt run the same code
	unsigned int seed = (unsigned int)time(nullptr);
	SetRandomSeed(seed);
	// Useful to note what seed produces what results so we can reproduce odd games
	std::cout << "Random Seed: " << seed << "\n";

	std::ofstream csv("results.csv");
	if (!csv.is_open())
	{
		std::cout << "Could not open results.csv\n";
		return;
	}
	csv << "Experiment,game,aiA,settingA,aiB,settingB,aColour,winner,scoreForA,totalMoves,redAvgMs,yellowAvgMs,illegalMove\n";

	RunMatch("Head to head", AI_MINIMAX, 4, AI_MCTS, 1000, 20, 2, csv);

	std::cout << "\nDone. Results saved to results.csv\n";
}