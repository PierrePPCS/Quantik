#pragma once

#include "Enums.h"

struct Cell
{
public:
	PieceType m_Piece;
	PlayerType m_Player;
	int coord_x;
	int coord_y;
	Cell() :m_Piece(PIECE_NONE), m_Player(PLAYER_NONE), coord_x(-1), coord_y(-1) {}
};

