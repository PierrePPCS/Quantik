#pragma once

#include <vector>
#include "Params.h"
#include "Cell.h"
#include "Coord.h"
#include "Player.h"

class Board
{
public:
	std::vector<std::vector<Cell>> m_Cells;

public:

	Board();
	void GetLine(int i, std::vector<Cell>& line);
	void GetColumn(int j, std::vector<Cell>& column);
	void GetSquare(int i, int j, std::vector<Cell>& square);
	void GetSquare(int k, std::vector<Cell>& square);
	Cell GetCell(int i, int j);
	void mapping();
	bool is_in_board(int x, int y, int& i, int& j);
	bool is_available(int i, int j, PieceType piece_type, PlayerType player_type);
	void available_cells_by_type(PlayerType player_type, PieceType piece_type, std::vector<Coord>& available);
	void available_cells(const Player& player, std::vector<CoordType>& available);
	int score(PlayerType player_type,std::vector<Cell> zone);
	bool is_available_anytype(int i, int j, PieceType& piece_type, PlayerType player_type);
};


bool is_in_vector(std::vector<Cell> vector, PieceType piece_type, PlayerType player_type);



