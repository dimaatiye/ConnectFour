#include "Tournament.h"
#include <iostream>
#include <ctime>
#include "raylib.h"
#include "RandomAi.h"

char PlayGame(AiPlayer* t_red, AiPlayer* t_yellow)
{
	Board board;
	char currentPlayer = 'X';

	while (board.GetWinner() == ' ')
	{
		AiPlayer* currentAi = t_yellow;
		if (currentPlayer == 'X')
		{
			currentAi = t_red;
		}
		
		int column = currentAi->ChooseMove(board);
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

	return board.GetWinner();
}

void RunTournament()
{
	std::cout << "Tournament Mode\n";

	unsigned int seed = (unsigned int)time(nullptr);
	SetRandomSeed(seed);
	std::cout << "Random Seed: " << seed << "\n";

	RandomAi redAi('X');
	RandomAi yellowAi('O');

	for (int game = 1; game <= 10; game++)
	{
		char winner = PlayGame(&redAi, &yellowAi);
		std::cout << "Game: " << game << " Winner: " << winner << "\n";
	}
}