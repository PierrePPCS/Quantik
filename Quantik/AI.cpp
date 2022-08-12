#include <vector>
#include "AI.h"
#include "Player.h"
#include "Board.h"
#include "Utils.h"

bool AI::play_dumb()
{
	std::vector<CoordType> available;
	GetPlayer()->GetBoard()->available_cells(*GetPlayer(), available);
	int k = available.size();
	printf("IA: %i moves available\n", k);
	if (k == 0)
		return false;
	int rand = std::rand() * k / (RAND_MAX + 1);
	const CoordType& coordtype = available[rand];
	if (is_in_vector(GetPlayer()->playerboard, coordtype.piece_type, GetPlayer()->player_type) )
	{
		GetPlayer()->GetBoard()->m_Cells[coordtype.i][coordtype.j].m_Piece = coordtype.piece_type;
		GetPlayer()->GetBoard()->m_Cells[coordtype.i][coordtype.j].m_Player = GetPlayer()->player_type;
		GetPlayer()->delete_piece(coordtype.piece_type);
		return true;
	}
	return false;
}


