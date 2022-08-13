#include "Utils.h"
#include <vector>
#include "Cell.h"
#include "Player.h"

PlayerType get_other(PlayerType player_type)
{
	if (player_type == PLAYER_1)
		return PLAYER_2;
	return PLAYER_1;
}

void draw_triangle(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end)
{

	int x_mil = (x_beg + x_end) / 2;
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_mil, y_end);
	SDL_RenderDrawLine(renderer, x_mil, y_end, x_end, y_beg);
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_end, y_beg);
}

void draw_diagonal(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end)
{
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_end, y_end);
}

void draw_square(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end)
{
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_end, y_beg);
	SDL_RenderDrawLine(renderer, x_beg, y_end, x_end, y_end);
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_beg, y_end);
	SDL_RenderDrawLine(renderer, x_end, y_end, x_end, y_beg);
}


int draw_circle(SDL_Renderer* renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;
	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) 
	{
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

		if (status < 0) 
		{
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) 
		{
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) 
		{
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else 
		{
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}






void suppr(std::vector<Cell> zone,std::vector<Cell>& vector, PieceType piece_type, PlayerType player_type)
{
	for (int i = 0; i < BOARD_DIM; i++)
	{
		if (!(zone[i].m_Piece == piece_type)&&(zone[i].m_Player==get_other(player_type)))
			vector.push_back(zone[i]);
	}

}


void sort_coordscore(std::vector<CoordScore>& scores)
{
	int k = scores.size();
	for (int i = 0; i < k; i++)
	{
		for (int j = i+1; j < k; j++)
		{
			if (scores[i].Score < scores[j].Score)
			{
				CoordScore temp = scores[i];
				scores[i] = scores[j];
				scores[j] = temp;
			}
		}
	}

}


