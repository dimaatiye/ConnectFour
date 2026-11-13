#pragma once
#include "Board.h"

class AiPlayer
{
protected:
	char m_myPiece;
	char m_opponentPiece;

public:
	AiPlayer(char t_myPiece)
	{
		m_myPiece = t_myPiece;

		if (m_myPiece == 'X')
		{
			m_opponentPiece = 'O';
		}
		else
		{
			m_opponentPiece = 'X';
		}
	}

	virtual ~AiPlayer() {}

	virtual int ChooseMove(Board board) = 0;
	virtual void SetDifficulty(int t_difficulty) = 0;
};

