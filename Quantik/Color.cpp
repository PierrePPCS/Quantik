#include "Color.h"

Color red(255, 0, 0, 255);
Color green(0, 255, 0, 255);
Color blue(0, 0, 255, 255);
Color white(255, 255, 255, 255);
Color black(0, 0, 0, 255);

void Color::SetDrawColor(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

