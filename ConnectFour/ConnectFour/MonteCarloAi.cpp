#include "MonteCarloAi.h"

void MonteCarloAi::SetDifficulty(int t_difficulty)
{
	m_iterations = t_difficulty;
}

int MonteCarloAi::ChooseMove(Board t_board)
{
	// This is where the Monte Carlo implementation will live
	return 0;
}

double MonteCarloAi::CalculateUCT(Node* t_node)
{
	if (t_node->visits == 0)
	{
		return INFINITY;
	}
	// LHS of the formula
	double exploitation = (double)t_node->wins / t_node->visits;
	//RHS of the formula
	double exploration = m_exploration * std::sqrt(std::log((double)t_node->parent->visits) / t_node->visits);

	return exploitation + exploration;
}
