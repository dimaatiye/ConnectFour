#include "Tournament.h"
#include <iostream>
#include <ctime>
#include "raylib.h"
#include "RandomAi.h"

void RunTournament()
{
	std::cout << "Tournament Mode\n";

	unsigned int seed = (unsigned int)time(nullptr);
	SetRandomSeed(seed);
	std::cout << "Random Seed: " << seed << "\n";

	RandomAi testAi('X');
	Board testBoard;
	for (int i = 0; i < 5; i++)
	{
		std::cout << "Random Ai picked column: " << testAi.ChooseMove(testBoard) << "\n";
	}
}