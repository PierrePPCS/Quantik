#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Params.h"
#include "Board.h"
#include "AI.h"

struct SDL_Renderer;

struct Color
{
	int r, g, b, a;

	Color(int _r = 255, int _g = 255, int _b = 255, int _a = 255)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	void SetDrawColor(SDL_Renderer* renderer);
};

extern Color red, green, blue, white, black;

class APP 
{
public:
	Player_board playerboard1;
	Player_board playerboard2;
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
	void Hilight(const Player_board& player_board, const Board& board);
	void draw();
	bool check_victory(int i, int j);
	Player_board& current_playerboard();
};


extern APP app;

