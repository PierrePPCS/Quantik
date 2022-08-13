#pragma once

#include "Enums.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include <vector>
#include "Cell.h"
#include "Params.h"
#include "Coord.h"

PlayerType get_other(PlayerType player_type);
void draw_triangle(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end);
void draw_diagonal(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end);
void draw_square(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end);
int draw_circle(SDL_Renderer* renderer, int x, int y, int radius);
void suppr(std::vector<Cell> zone, std::vector<Cell>& vector, PieceType piece_type, PlayerType player_type);
void sort_coordscore(std::vector<CoordScore>& scores);