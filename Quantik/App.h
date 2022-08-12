#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Player.h"
#include "Board.h"

class APP
{
public:
	Player playerboard1;
	Player playerboard2;
	Board board;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int mouse_x, mouse_y;
	int button;
	int dragged_source_cell;
	PlayerType current_player = PLAYER_1;


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
	bool check_victory(int i, int j);
	bool soon_to_win(PieceType& final_piece, int& i, int& j, PlayerType current_player);
	Player& current_playerboard();
};

