#include <vector>
#include "AI.h"
#include "Player.h"
#include "Board.h"
#include "Utils.h"

bool AI::play_dumb()
{
	std::vector<CoordType> available;
	GetPlayer()->GetBoard()->available_cells(*GetPlayer(), available);
	size_t k = available.size();
	printf("IA: %zi moves available\n", k);
	if (k == 0)
		return false;
	int rand = std::rand() * k / (RAND_MAX + 1);
	const CoordType& coordtype = available[rand];
	if (is_in_vector(GetPlayer()->playerboard, coordtype.piece_type, GetPlayer()->player_type) )
	{
		return GetPlayer()->play(coordtype.i, coordtype.j, coordtype.piece_type);
	}
	return false;
}


bool AI::playsmart()
{
	std::vector<CoordScore> scores;
	std::vector<CoordType> available;
	GetPlayer()->GetBoard()->available_cells(*GetPlayer(), available);
	printf("IA: %zi moves available\n", available.size());
	if (available.size() == 0)
		return false;
	CoordScore adversary = best_adversary_score();
	for (int k = 0; k < available.size(); k++)
	{
		std::vector<Cell> Line;
		std::vector<Cell> Column;
		std::vector<Cell> Square;
		Cell& c = GetPlayer()->GetBoard()->m_Cells[available[k].i][available[k].j];
		c.m_Piece = available[k].piece_type;
		c.m_Player = GetPlayer()->player_type;
		GetPlayer()->GetBoard()->GetSquare(available[k].i, available[k].j, Square);
		GetPlayer()->GetBoard()->GetLine(available[k].i, Line);
		GetPlayer()->GetBoard()->GetColumn(available[k].j, Column);
		int max = std::max(std::max(GetPlayer()->GetBoard()->score(GetPlayer()->player_type, Line), GetPlayer()->GetBoard()->score(GetPlayer()->player_type, Column)), GetPlayer()->GetBoard()->score(GetPlayer()->player_type, Square));
		c.m_Piece = PIECE_NONE;
		c.m_Player = PLAYER_NONE;
		Coord co(available[k].i, available[k].j);
		CoordType c_t(co, available[k].piece_type);
		scores.push_back(CoordScore(c_t, max));


	}
	PieceType final_piece;
	sort_coordscore(scores);
	CoordScore& next_move = scores[0];
	if (next_move.Score>adversary.Score)
		return GetPlayer()->play(next_move.i, next_move.j, next_move.piece_type);
	else if (GetPlayer()->GetBoard()->is_available_anytype(adversary.i, adversary.j, final_piece, GetPlayer()->player_type ))
		return GetPlayer()->play(adversary.i, adversary.j, final_piece);
	else 
		return GetPlayer()->play(next_move.i, next_move.j, next_move.piece_type);
}


CoordScore AI::best_adversary_score()
{
	std::vector<CoordScore> scores;
	std::vector<CoordType> available;
	const Player& Opponent = GetPlayer()->GetOpponent();
	Board* pBoard = Opponent.GetBoard();
	pBoard->available_cells(Opponent, available);
	for (int k = 0; k < available.size(); k++)
	{
		std::vector<Cell> Line;
		std::vector<Cell> Column;
		std::vector<Cell> Square;
		Cell& c = pBoard->m_Cells[available[k].i][available[k].j];
		c.m_Piece = available[k].piece_type;
		c.m_Player = Opponent.player_type;
		pBoard->GetSquare(available[k].i, available[k].j, Square);
		pBoard->GetLine(available[k].i, Line);
		pBoard->GetColumn(available[k].j, Column);
		int max = std::max(std::max(GetPlayer()->GetBoard()->score(Opponent.player_type, Line),GetPlayer()->GetBoard()->score(Opponent.player_type, Column)), GetPlayer()->GetBoard()->score(Opponent.player_type, Square));
		c.m_Piece = PIECE_NONE;
		c.m_Player = PLAYER_NONE;
		Coord co(available[k].i, available[k].j);
		CoordType c_t(co, available[k].piece_type);
		scores.push_back(CoordScore(c_t, max));

	}
	sort_coordscore(scores);
	return scores[0];

}