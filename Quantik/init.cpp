#include "init.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "iostream"
#include "Params.h"
//#include "Board.h"

APP app;

Player& APP::current_playerboard() {
	if (current_player == PLAYER_1)
		return playerboard1;
	else
		return playerboard2;

}
