#include "Params.h"
#include "App.h"
#include "Player.h"
#include "Board.h"

Player::Player(Board *_pBoard)
{
	pBoard = _pBoard;
}

Player::~Player()
{
	if (ai)
	{
		delete ai;
		ai = nullptr;
	}
}

bool Player::delete_piece(PieceType piece_type)
{
	for (int i = 0; i< BOARD_DIM * 2; i++)
	{
		if (playerboard[i].m_Piece == piece_type)
		{
			playerboard[i].m_Piece = PIECE_NONE;
			return true;
		}
	}
	return false;
}

void Player::Player_board_init()
{
	playerboard.resize(BOARD_DIM * 2);
	for (int i = 0; i < BOARD_DIM * 2; i++)
		playerboard[i].m_Player = player_type;
	playerboard[0].m_Piece = PIECE_TRIANGLE;
	playerboard[4].m_Piece = PIECE_TRIANGLE;
	playerboard[1].m_Piece = PIECE_CIRCLE;
	playerboard[5].m_Piece = PIECE_CIRCLE;
	playerboard[2].m_Piece = PIECE_SQUARE;
	playerboard[6].m_Piece = PIECE_SQUARE;
	playerboard[3].m_Piece = PIECE_CYLINDER;
	playerboard[7].m_Piece = PIECE_CYLINDER;
}



void Player::player_mapping_1()
{
	for (int i = 0; i < BOARD_DIM; i++)
	{
		playerboard[i].coord_x = i * 100;
		playerboard[i].coord_y = 0;
		playerboard[i + BOARD_DIM].coord_x = i * 100;
		playerboard[i + BOARD_DIM].coord_y = 100;
	}
}

void Player::player_mapping_2()
{
	for (int i = 0; i < BOARD_DIM; i++)
	{
		playerboard[i].coord_y = i * 100 + 300;
		playerboard[i].coord_x = 500;
		playerboard[i + BOARD_DIM].coord_y = i * 100 + 300;
		playerboard[i + BOARD_DIM].coord_x = 600;
	}
}

void Player::SetAI(bool bAI)
{
	if (bAI) // on veut une IA
	{
		if (IsAI())
		{
			// rien à faire, on en a déjà une
		}
		else
		{
			ai = new AI(this);
		}
	}
	else // pas d'IA
	{
		if (IsAI())
		{
			delete ai;
			ai = nullptr;
		}
		else
		{
			// rien à faire, on n'en a pas
		}
	}
}

void Player::p_cell_from_coord(int x, int y, int& i)
{
	for (int k = 0; k < BOARD_DIM; k++)
	{
		const Cell& cell = playerboard[k];
		if ((x < cell.coord_x + 100) && (x > cell.coord_x) && (y < cell.coord_y + 100) && (y > cell.coord_y))
		{
			i = k;
		}
	}
}

bool Player::is_in_playerboard(int x, int y, int& icell) const
{
	for (int j = 0; j < BOARD_DIM * 2; j++)
	{
		const Cell& C = playerboard[j];
		if ((x < C.coord_x + 100) && (x > C.coord_x) && (y < C.coord_y + 100) && (y > C.coord_y))
		{
			icell = j;
			return true;
		}
	}
	return false;
}

bool Player::play(int i, int j, PieceType piece_type)
{
	if (!delete_piece(piece_type))
		return false;
	Cell& c = GetBoard()->m_Cells[i][j];
	c.m_Player = player_type;
	c.m_Piece = piece_type;
	app.check_victory();
	return true;
}

bool Player::play(int i, int j, int dragged_piece)
{
	Cell& pc = playerboard[dragged_piece];
	Cell& c = GetBoard()->m_Cells[i][j];
	c.m_Player = player_type;
	c.m_Piece = pc.m_Piece;
	pc.m_Piece = PIECE_NONE;
	app.check_victory();
	return true;

}

const Player& Player::GetOpponent()
{
	return app.GetOpponent(player_type);
}
