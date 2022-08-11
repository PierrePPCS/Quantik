#include "Board.h"


bool is_in_vector(std::vector<Cell> vector, PieceType piece_type, PlayerType player_type) {
	int i;
	for (i = 0; i < vector.size(); i++) {
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
	return ((GetCell(i, j).m_Piece == PIECE_NONE) && (not is_in_vector(line, piece_type, get_other(player_type))) && (not is_in_vector(colomn, piece_type, get_other(player_type))) && (not is_in_vector(square, piece_type, get_other(player_type))));

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


void Player_board::Player_board_init()
{
	playerboard.resize(BOARD_DIM * 2);
	for (int i = 0; i< BOARD_DIM * 2; i++)
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

void Board::GetSquare(int i, int j, std::vector<Cell>& column)
{
	column.resize(BOARD_DIM);
	i = i / 2;
	j = j / 2;
	int indice = -1;
	for (int k = 0; k < 2; k++)
		for (int h = 0; h < 2; h++) {
			indice++;
			column[indice] = m_Cells[i*2 + k][j*2 + h];
		}

}



void Board::mapping() {
	for (int i = 0; i < BOARD_DIM; i++) {
		for (int j = 0; j < BOARD_DIM; j++) {
			m_Cells[i][j].coord_x = j * 100;
			m_Cells[3-i][j].coord_y = 700 - i * 100;
		}
	}
}

void Player_board::player_mapping_1() {
	for (int i = 0; i < BOARD_DIM; i++) {
		playerboard[i].coord_x = i * 100;
		playerboard[i].coord_y = 0;
		playerboard[i+4].coord_x = i * 100;
		playerboard[i + 4].coord_y = 100;



	}
}

void Player_board::player_mapping_2() {
	for (int i = 0; i < BOARD_DIM; i++) {
		playerboard[i].coord_y = i * 100 + 300;
		playerboard[i].coord_x = 500;
		playerboard[i + 4].coord_y = i * 100 + 300;
		playerboard[i + 4].coord_x = 600;
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


void Board::change_cell(int i, int j, PieceType piece_type, PlayerType player_type) {
	m_Cells[i][j].m_Player = player_type;
	m_Cells[i][j].m_Piece = piece_type;
}

void Player_board::p_cell_from_coord(int x, int y, int& i) {
	for (int k = 0; k < BOARD_DIM; k++) {
		Cell cell = playerboard[k];
		if ((x < cell.coord_x + 100) && (x > cell.coord_x) && (y < cell.coord_y + 100) && (y > cell.coord_y)) {
			i = k;
		}
	}
}

void Board::available_cells_by_type(PlayerType player_type,PieceType piece_type, std::vector<Coord>& available) {
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


void Board::available_cells(PlayerType player_type, std::vector<CoordType>& available) {
	PlayerType adversary = get_other(player_type);
	std::vector<Coord> available_by_type;
	for (int k = PIECE_TRIANGLE; k <= PIECE_CYLINDER; k++) {
		PieceType piece_type =(PieceType)k;
		available_cells_by_type(adversary, piece_type, available_by_type);
		for (int j = 0; j < available_by_type.size(); j++)
			available.push_back(CoordType(available_by_type[j], piece_type));
	}
}


