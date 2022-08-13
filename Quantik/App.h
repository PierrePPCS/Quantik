#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Player.h"
#include "Board.h"

class APP
{
public:
	Player player1;
	Player player2;
	Board board;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int mouse_x, mouse_y;
	int button;
	int dragged_source_cell;
	PlayerType current_player_type = PLAYER_1;
	int victory = 0;


public:
	APP();
	bool IsDragging() { return dragged_source_cell != -1; }
	void initSDL();
	void draw_board();
	void doInput();
	void draw_Pieces();
	void other_player();
	void Hilight(const Player& player_board, const Board& board);
	void draw();
	bool check_local_victory(int i, int j);
	void check_victory();
	Player& current_player();

};

extern APP app;
