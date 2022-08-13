#pragma once

#include<vector>
#include "Cell.h"
#include "AI.h"

class Board;

class Player
{
public:
	std::vector<Cell> playerboard;
	PlayerType player_type = PLAYER_NONE;
	AI* ai = nullptr;
public:
	Player(Board* _pBoard = nullptr);
	~Player();
	void Player_board_init();
	void player_mapping_1();
	void player_mapping_2();
	void p_cell_from_coord(int x, int y, int& i);
	void SetAI(bool bAI);
	bool IsAI() { return ai != nullptr; }
	bool is_in_playerboard(int x, int y, int& icell) const;
	void SetBoard(Board* _pBoard) { pBoard = _pBoard; }
	Board* GetBoard() { return pBoard; }
	bool delete_piece(PieceType piece_type);
	bool play(int i, int j, PieceType piece_type);
	bool play(int i, int j, int dragged_piece);
private:
	Board* pBoard = nullptr;

};

