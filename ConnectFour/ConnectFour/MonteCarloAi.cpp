#include "MonteCarloAi.h"

void MonteCarloAi::SetDifficulty(int t_difficulty)
{
	// Default values
	m_exploration = std::sqrt(2.0);
	m_iterations = t_difficulty;
}

int MonteCarloAi::ChooseMove(Board t_board)
{
	if (t_board.GetValidMoves().empty())
	{
		return -1;
	}

	Node* root = new Node(t_board, -1, m_opponentPiece, nullptr);

	for (int i = 0; i < m_iterations; i++)
	{
		Node* leaf = Select(root);
		Node* nodeToSimulate = Expand(leaf);
		char result = Simulate(nodeToSimulate);
		BackPropagate(nodeToSimulate, result);
	}

	Node* bestChild = root->children[0];
	for (int i = 1; i < (int)root->children.size(); i++)
	{
		if (root->children[i]->visits > bestChild->visits)
		{
			bestChild = root->children[i];
		}
	}

	int bestMove = bestChild->move;

	DeleteTree(root);

	return bestMove;
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

Node* MonteCarloAi::Select(Node* t_node)
{
	Node* current = t_node;
	
	// if children is empty we have reached the frontier
	while (!current->children.empty())
	{
		// Assume the first child is best 
		Node* bestChild = current->children[0];
		double bestUCT = CalculateUCT(bestChild);

		for (int i = 1; i < (int)current->children.size(); i++)
		{
			// Work out the UCT for each child of the current node
			double uct = CalculateUCT(current->children[i]);

			if (uct > bestUCT)
			{
				bestUCT = uct;
				bestChild = current->children[i];
			}
		}
		// Set the currently explored node to be the best one found in the loop, then if it has child nodes, run the loop for those
		current = bestChild;
	}

	return current;
}


Node* MonteCarloAi::Expand(Node* t_node)
{
	std::vector<int> moves = t_node->board.GetValidMoves();

	// If no valid moves exist return the argument node
	if (moves.empty())
	{
		return t_node;
	}

	char nextPlayer;
	if (t_node->playerWhoMoved == 'X')
	{
		nextPlayer = 'O';
	}
	else
	{
		nextPlayer = 'X';
	}

	for (int i = 0; i < (int)moves.size(); i++)
	{
		Board childBoard = t_node->board;
		childBoard.MakeMove(moves[i], nextPlayer);

		Node* child = new Node(childBoard, moves[i], nextPlayer, t_node);
		t_node->children.push_back(child);
	}

	return t_node->children[0];
}

char MonteCarloAi::Simulate(Node* t_node)
{
	Board board = t_node->board;

	char currentPlayer;
	if (t_node->playerWhoMoved == 'X')
	{
		currentPlayer = 'O';
	}
	else
	{
		currentPlayer = 'X';
	}

	// Keeps running till a win happens or the board is full
	while (board.GetWinner() == ' ')
	{
		std::vector<int> moves = board.GetValidMoves();
		// Make random move from the vector of valid moves
		int randomIndex = GetRandomValue(0, (int)moves.size() - 1);
		board.MakeMove(moves[randomIndex], currentPlayer);

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

void MonteCarloAi::BackPropagate(Node* t_node, char t_result)
{
	Node* current = t_node;

	// The root of the tree has no parent node so when NullPtr is found, the loop will stop
	while (current != nullptr)
	{
		current->visits++;

		if (current->playerWhoMoved == t_result)
		{
			current->wins++;
		}
		// Move backwards up the tree
		current = current->parent;
	}
}

void MonteCarloAi::DeleteTree(Node* t_node)
{
	for (int i = 0; i < (int)t_node->children.size(); i++)
	{
		DeleteTree(t_node->children[i]);
	}
	delete t_node;
}
