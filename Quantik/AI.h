#pragma once
#include "Board.h"



class AI
{public:
	PlayerType player_type;
	Board board;
	void play_dumb();
	bool soon_to_win(int& i, int& j);
};
