#pragma once

#include "Coord.h"
#include <algorithm>
#include "Utils.h"

class Player;
class AI
{

public:
	AI(Player* _pPlayer) { pPlayer = _pPlayer; }
	bool play_dumb();
	bool soon_to_win(int& i, int& j, Player adversary);
	Player* GetPlayer() { return (pPlayer); }
	bool playsmart();
	CoordScore best_adversary_score();

private:
	Player* pPlayer = nullptr;
	

	
};

