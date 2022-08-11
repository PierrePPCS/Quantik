#include "AI.h"



void AI::play_dumb() {
	std::vector<CoordType> available;
	int k = available.size();
	int rand = std::rand() / (RAND_MAX + 1) * k;
	CoordType coordtype = available[rand];
	board.m_Cells[coordtype.i][coordtype.j].m_Piece = coordtype.piece_type;
	board.m_Cells[coordtype.i][coordtype.j].m_Player = player_type;
}


bool AI::soon_to_win(int& i, int& j) {
	PlayerType adversary = get_other(player_type);
	std::vector<CoordType> available;
	board.available_cells(adversary,available);
	int k = available.size();
	return false;
}