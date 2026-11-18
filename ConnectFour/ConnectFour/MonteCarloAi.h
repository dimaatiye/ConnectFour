#pragma once
#include "AiPlayer.h"
#include <vector>
#include <cmath>

struct Node {
	Board board; // The game position at this node
	int move; // The column a piece was placed in to reach this node from its parent
	char playerWhoMoved; // Either X or O

	Node* parent;
	std::vector<Node*> children;

	int visits;
	int wins;

	Node(Board t_board, int t_move, char t_playerWhoMoved, Node* t_parent)
	{
		board = t_board;
		move = t_move;
		playerWhoMoved = t_playerWhoMoved;
		parent = t_parent;
		visits = 0;
		wins = 0;
	}
};

class MonteCarloAi: public AiPlayer
{
private:
	int m_iterations; // This is what difficulty will change
	double m_exploration; // This is the C from the formula!
public:
	MonteCarloAi(char t_myPiece) : AiPlayer(t_myPiece)
	{
		// m_iterations = number
		m_exploration = std::sqrt(2.0);
	}

	void SetDifficulty(int t_difficulty) override;
	int ChooseMove(Board t_board) override;
	double CalculateUCT(Node* t_node); // Calculates the upper confidence bound for the tree search
	Node* Select(Node* t_node); // Start at the root and if it has children, work out their UCT and find the best, then explore that nodes children until the frontier is found
};

