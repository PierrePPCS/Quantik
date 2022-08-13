#include "Board.h"
#include "AI.h"
#include "Utils.h"
#include "Player.h"


bool is_in_vector(std::vector<Cell> vector, PieceType piece_type, PlayerType player_type)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i].m_Piece == piece_type && vector[i].m_Player == player_type)
			return true;
	}
	return false;
}



bool Board::is_available(int i, int j, PieceType piece_type, PlayerType player_type) {
	std::vector<Cell> line;
	std::vector<Cell> colomn;
	std::vector<Cell> square;
	GetLine(i, line);
	GetColumn(j, colomn);
	GetSquare(i, j, square);
	return ((GetCell(i, j).m_Piece == PIECE_NONE) && (!is_in_vector(line, piece_type, get_other(player_type))) && (!is_in_vector(colomn, piece_type, get_other(player_type))) && (!is_in_vector(square, piece_type, get_other(player_type))));

}

Board::Board()
{
	m_Cells.resize(BOARD_DIM);
	for (int i = 0; i < BOARD_DIM; i++)
		m_Cells[i].resize(BOARD_DIM);
}

void Board::GetColumn(int j, std::vector<Cell>& line)
{
	line.resize(BOARD_DIM);
	for (int i = 0; i < BOARD_DIM; i++)
		line[i] = m_Cells[i][j];

}

void Board::GetLine(int i, std::vector<Cell>& column)
{
	column.resize(BOARD_DIM);
	for (int j = 0; j < BOARD_DIM; j++)
		column[j] = m_Cells[i][j];
}

Cell Board::GetCell(int i, int j)
{
	return m_Cells[i][j];
}


void Board::GetSquare(int i, int j, std::vector<Cell>& square)
{
	square.resize(BOARD_DIM);
	i = i / 2;
	j = j / 2;
	int indice = -1;
	for (int k = 0; k < 2; k++)
		for (int h = 0; h < 2; h++) {
			indice++;
			square[indice] = m_Cells[i*2 + k][j*2 + h];
		}

}

void Board::GetSquare(int k, std::vector<Cell>& square)
{
	GetSquare((k / 2) * 2, (k % 2) * 2, square);
}


void Board::mapping() {
	for (int i = 0; i < BOARD_DIM; i++) {
		for (int j = 0; j < BOARD_DIM; j++) {
			m_Cells[i][j].coord_x = j * 100;
			m_Cells[3-i][j].coord_y = 700 - i * 100;
		}
	}
}

bool Board::is_in_board(int x, int y, int& i, int& j)
{
	for (int k = 0; k < BOARD_DIM; k++)
	{
		for (int l = 0; l < BOARD_DIM; l++)
		{
			Cell cell = m_Cells[k][l];
			if ((x < cell.coord_x + 100) && (x > cell.coord_x) && (y < cell.coord_y) && (y > cell.coord_y - 100))
			{
				i = k;
				j = l;
				return true;
			}
		}
	}
	return false;
}

void Board::available_cells_by_type(PlayerType player_type,PieceType piece_type, std::vector<Coord>& available)
{
	std::vector<std::vector<bool>> vector;
	vector.resize(BOARD_DIM);
	for (int i = 0; i < BOARD_DIM; i++) 
		vector[i].resize(BOARD_DIM);
	for (int i = 0; i < BOARD_DIM; i++)
	{
		for (int j = 0; j < BOARD_DIM; j++)
		{
			vector[i][j] = is_available(i, j, piece_type, player_type);
		}
	}
	for (int i = 0; i < BOARD_DIM; i++)
		for (int j = 0; j < BOARD_DIM; j++)
			if (vector[i][j])
				available.push_back(Coord(i, j));
}


void Board::available_cells(const Player& player, std::vector<CoordType>& available) 
{
	for (int k = PIECE_TRIANGLE; k <= PIECE_CYLINDER; k++)
	{
		PieceType piece_type =(PieceType)k;
		if (is_in_vector(player.playerboard, piece_type, player.player_type))
		{
			std::vector<Coord> available_by_type;
			available_cells_by_type(player.player_type, piece_type, available_by_type);
			for (int j = 0; j < available_by_type.size(); j++)
				available.push_back(CoordType(available_by_type[j], piece_type));
		}
	}
}


int Board::score(PlayerType player_type, std::vector<Cell> zone)
{
	int score = 0;
	std::vector<bool> seen = { false,false,false,false };
	for (int i = 0; i < BOARD_DIM; i++)
	{
		Cell c = zone[i];
		if (player_type == get_other(c.m_Player))
			return -1;
		if (player_type == c.m_Player)
		{
			if (!seen[c.m_Piece - 1])
			{
				seen[c.m_Piece - 1] = true;
				score++;
			}
			else
				return -1;
		}

	}
	return score;
}