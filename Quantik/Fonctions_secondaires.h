#pragma once
#include <iostream>
#include <string>
#include "Board.h"
#include "vector"
#include "Params.h"

/*bool is_in_vector(std::vector < Cell> vector, PieceType element) {

	bool is;
	is = false;
	for (int i = 0; i < vector.size(); i++)
		if (element == vector[i].m_Piece)
			is = true;
	return is;
};

bool test_victory(PlayerType player_type, std::vector <Cell> line) {
	bool bol = false;
	if ((is_in_vector(line, PIECE_TRIANGLE)) && (is_in_vector(line, PIECE_SQUARE)) && (is_in_vector(line, PIECE_CIRCLE)) && (is_in_vector(line, PIECE_CYLINDER)))
		if (line[0].m_Player == line[1].m_Player == line[2].m_Player == line[3].m_Player == player_type)
			bol = true;
	return bol;
			
	
}


bool test_victoire(Board board, PlayerType player_type ,int i, int j) {
	std::vector < Cell> column;
	board.GetColumn(j, column);
	std::vector < Cell> ligne;
	board.GetLine(i, ligne);
	std::vector < Cell> square;
	board.GetSquare(i,j, square);
	return test_victory(player_type, column) || test_victory(player_type, ligne) || test_victory(player_type, square);
}
*/











