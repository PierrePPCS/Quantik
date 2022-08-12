#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"

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
