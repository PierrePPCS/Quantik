#pragma once

#include <vector>
#include "Params.h"

enum PieceType
{
	PIECE_NONE,
	PIECE_TRIANGLE,
	PIECE_CIRCLE,
	PIECE_SQUARE,
	PIECE_CYLINDER
};

enum PlayerType
{
	PLAYER_NONE,
	PLAYER_1,
	PLAYER_2
};

struct Cell
{
public:
	PieceType m_Piece;
	PlayerType m_Player;
	int coord_x;
	int coord_y;
	Cell() :m_Piece(PIECE_NONE), m_Player(PLAYER_NONE) {}
};



struct Coord
{
	int i, j;
	Coord() { i = -1; j = -1; }
	Coord(int _i, int _j) { i = _i; j =_j; }

};


struct CoordType:public Coord
{
	PieceType piece_type;
	CoordType() { piece_type = PIECE_NONE; }
	CoordType(Coord& coord, PieceType _piece_type) { i = coord.i; j = coord.j; piece_type = _piece_type; }
};

struct Player_board
{
public:
	std::vector<Cell> playerboard;
	PlayerType player_type;
public:
	void Player_board_init();
	void player_mapping_1();
	void player_mapping_2();
	void p_cell_from_coord(int x, int y, int& i);
};

class Board
{
public:
	std::vector<std::vector<Cell>> m_Cells;

public:

	Board();
	void GetLine(int i, std::vector<Cell>& line);
	void GetColumn(int j, std::vector<Cell>& column);
	void GetSquare(int i, int j, std::vector<Cell>& column);
	Cell GetCell(int i, int j);
	void mapping();
	bool is_in_board(int x, int y, int& i, int& j);
	void change_cell(int i, int j, PieceType piece_type, PlayerType player_type);
	bool is_available(int i, int j, PieceType piece_type, PlayerType player_type);
	void available_cells_by_type(PlayerType player_type, PieceType piece_type, std::vector<Coord>& available);
	void available_cells(PlayerType player_type, std::vector<CoordType>& available);
};


bool is_in_vector(std::vector<Cell> vector, PieceType piece_type, PlayerType player_type);
PlayerType get_other(PlayerType player_type);



