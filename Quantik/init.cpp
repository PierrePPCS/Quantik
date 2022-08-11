#include "init.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "iostream"
#include "Params.h"
//#include "Board.h"

Color red(255, 0, 0, 255);
Color green(0, 255, 0, 255);
Color blue(0, 0, 255, 255);
Color white(255, 255, 255, 255);
Color black(0, 0, 0, 255);

APP app;




void Color::SetDrawColor(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void draw_triangle(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end) {

	int x_mil = (x_beg + x_end) / 2;
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_mil, y_end);
	SDL_RenderDrawLine(renderer, x_mil, y_end, x_end, y_beg);
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_end, y_beg);
}

void draw_diagonal(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end) {
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_end, y_end);
}


void draw_square(SDL_Renderer* renderer, int x_beg, int x_end, int y_beg, int y_end) {
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_end, y_beg);
	SDL_RenderDrawLine(renderer, x_beg, y_end, x_end, y_end);
	SDL_RenderDrawLine(renderer, x_beg, y_beg, x_beg, y_end);
	SDL_RenderDrawLine(renderer, x_end, y_end, x_end, y_beg);
}


int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
	int offsetx, offsety, d;
	int status;
	offsetx = 0;
	offsety = radius;
	d = radius - 1;
	status = 0;

	while (offsety >= offsetx) {
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
		status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
		status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
		status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

		if (status < 0) {
			status = -1;
			break;
		}

		if (d >= 2 * offsetx) {
			d -= 2 * offsetx + 1;
			offsetx += 1;
		}
		else if (d < 2 * (radius - offsety)) {
			d += 2 * offsety - 1;
			offsety -= 1;
		}
		else {
			d += 2 * (offsety - offsetx - 1);
			offsety -= 1;
			offsetx += 1;
		}
	}

	return status;
}


void draw_highlight(const Cell& C, PieceType piece_type, const APP& app) {
	green.SetDrawColor(app.renderer);
	switch (piece_type) {
	case PIECE_SQUARE:
		draw_square(app.renderer, C.coord_x, C.coord_x + 100, C.coord_y, C.coord_y + 100);
		break;
	case PIECE_CIRCLE:
		SDL_RenderDrawCircle(app.renderer, C.coord_x + 50, C.coord_y + 50, 50);
		break;
	case PIECE_CYLINDER:
		draw_diagonal(app.renderer, C.coord_x, C.coord_x + 100, C.coord_y, C.coord_y + 100);
		break;
	case PIECE_TRIANGLE:
		draw_triangle(app.renderer, C.coord_x, C.coord_x + 100, C.coord_y, C.coord_y + 100);
		break;
	}
}

Player_board& APP::current_playerboard() {
	if (current_player == PLAYER_1)
		return playerboard1;
	else
		return playerboard2;

}

bool is_in_playerboard(Player_board board, int x, int y, int &icell) 
{
	for (int j = 0; j < BOARD_DIM * 2; j++) {
		Cell C = board.playerboard[j];
		if ((x < C.coord_x + 100) && (x > C.coord_x) && (y < C.coord_y + 100) && (y > C.coord_y))
		{
			icell = j;
			return true;
		}
	}
	return false;
}

PlayerType get_other(PlayerType player_type) {
	if (player_type == PLAYER_1)
		return PLAYER_2;
	return PLAYER_1;

}

APP::APP()
{
	dragged_source_cell = -1;
}


bool APP::check_victory(int i, int j) {
	std::vector<Cell> square;
	board.GetSquare(i, j, square);
	std::vector<Cell> line;
	std::vector<Cell> colomn;
	board.GetLine(i, line);
	board.GetColumn(j, colomn);
	if (is_in_vector(line, PIECE_CIRCLE, current_player) && is_in_vector(line, PIECE_CYLINDER, current_player) && is_in_vector(line, PIECE_SQUARE, current_player) && is_in_vector(line, PIECE_TRIANGLE, current_player))
		return true;
	if (is_in_vector(colomn, PIECE_CIRCLE, current_player) && is_in_vector(colomn, PIECE_CYLINDER, current_player) && is_in_vector(colomn, PIECE_SQUARE, current_player) && is_in_vector(colomn, PIECE_TRIANGLE, current_player))
		return true;
	if (is_in_vector(square, PIECE_CIRCLE, current_player) && is_in_vector(square, PIECE_CYLINDER, current_player) && is_in_vector(square, PIECE_SQUARE, current_player) && is_in_vector(square, PIECE_TRIANGLE, current_player))
		return true;
	return false;
}



void APP::Hilight(const Player_board& player_board, const Board& board)
{
	int x = 0;
	int y = 0;
	int boutons = SDL_GetMouseState(&x, &y);
	int icell = 0;
	if (is_in_playerboard(player_board, x, y, icell))
	{

		//std::cout << icell;
		PieceType piece_type = player_board.playerboard[icell].m_Piece;
		draw_highlight(player_board.playerboard[icell], piece_type, app);

	}
}

void APP::initSDL()
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;
	

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("WINDOW", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAP_WIDTH, MAP_HEIGHT, windowFlags);

	if (not window)
	{
		printf("Failed to open %d x %d window: %s\n", MAP_WIDTH, MAP_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	renderer = SDL_CreateRenderer(window, -1, rendererFlags);

	if (not renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
}


void APP::other_player()
{
	if (current_player == PLAYER_1)
		current_player = PLAYER_2;
	else
		current_player = PLAYER_1;


}


void APP::doInput()
{
	SDL_Event event;
	int cell;
	/*if (ai_turn == 1)
		ai.play_dumb();*/
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_MOUSEMOTION:
			button = SDL_GetMouseState(&mouse_x, &mouse_y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				button = SDL_GetMouseState(&mouse_x, &mouse_y);
				if (is_in_playerboard(current_playerboard(), mouse_x, mouse_y, cell) && current_playerboard().playerboard[cell].m_Piece != PIECE_NONE)
				{
					dragged_source_cell = cell;
				}
			};
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				button = SDL_GetMouseState(&mouse_x, &mouse_y);
				int i;
				int j;
				if (board.is_in_board(mouse_x, mouse_y, i, j) && IsDragging())
				{
					PieceType dragged_piece = current_playerboard().playerboard[dragged_source_cell].m_Piece;
					if (board.is_available(i,j,dragged_piece,current_player))
					{
						board.change_cell(i, j, current_playerboard().playerboard[dragged_source_cell].m_Piece, current_player);
						current_playerboard().playerboard[dragged_source_cell].m_Piece = PIECE_NONE;
						dragged_source_cell = -1;
						if (check_victory(i, j))
							printf("v");
						other_player();
					}
				}
			}
			break;
		}
	}
}


void APP::draw() {
	white.SetDrawColor(app.renderer);
	SDL_RenderDrawLine(renderer, 0, 0, 400, 0);
	SDL_RenderDrawLine(renderer, 0, 100, 400, 100);
	SDL_RenderDrawLine(renderer, 0, 200, 400, 200);
	SDL_RenderDrawLine(renderer, 0, 0, 0, 200);
	SDL_RenderDrawLine(renderer, 100, 0, 100, 200);
	SDL_RenderDrawLine(renderer, 200, 0, 200, 200);
	SDL_RenderDrawLine(renderer, 300, 0, 300, 200);
	SDL_RenderDrawLine(renderer, 400, 0, 400, 200);
	SDL_RenderDrawLine(renderer, 0, 700, 400, 700);
	SDL_RenderDrawLine(renderer, 0, 600, 400, 600);
	SDL_RenderDrawLine(renderer, 0, 500, 400, 500);
	SDL_RenderDrawLine(renderer, 0, 400, 400, 400);
	SDL_RenderDrawLine(renderer, 0, 300, 400, 300);
	SDL_RenderDrawLine(renderer, 0, 700, 0, 400);
	SDL_RenderDrawLine(renderer, 100, 700, 100, 300);
	SDL_RenderDrawLine(renderer, 200, 700, 200, 300);
	SDL_RenderDrawLine(renderer, 300, 700, 300, 300);
	SDL_RenderDrawLine(renderer, 400, 700, 400, 300);
	SDL_RenderDrawLine(renderer, 500, 300, 500, 700);
	SDL_RenderDrawLine(renderer, 600, 300, 600, 700);
	SDL_RenderDrawLine(renderer, 700, 300, 700, 700);
	SDL_RenderDrawLine(renderer, 500, 300, 700, 300);
	SDL_RenderDrawLine(renderer, 500, 400, 700, 400);
	SDL_RenderDrawLine(renderer, 500, 500, 700, 500);
	SDL_RenderDrawLine(renderer, 500, 600, 700, 600);
	SDL_RenderDrawLine(renderer, 500, 700, 700, 700);
	for (int i = 0; i < BOARD_DIM; i++) {
		for (int j = 0; j < BOARD_DIM; j++) {
			Cell cell = board.m_Cells[i][j];
			PieceType piece_type = cell.m_Piece;
			if (cell.m_Player == PLAYER_1)
				blue.SetDrawColor(app.renderer);
			else
				red.SetDrawColor(app.renderer);
			switch (piece_type) {

			case PIECE_TRIANGLE:
				draw_triangle(app.renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y - 100, cell.coord_y);
				break;
			case PIECE_CYLINDER:
				draw_diagonal(app.renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y - 100, cell.coord_y);
				break;
			case PIECE_SQUARE:
				draw_square(app.renderer, cell.coord_x + 10, cell.coord_x + 90, cell.coord_y - 90, cell.coord_y - 10);
				break;
			case PIECE_CIRCLE:
				SDL_RenderDrawCircle(app.renderer, cell.coord_x + 50, cell.coord_y - 50, 49);
				break;
				
			}
		}
	}
	for (int i = 0; i < BOARD_DIM*2; i++) {
		Cell cell = playerboard1.playerboard[i];
		PieceType piece_type = cell.m_Piece;
		if (cell.m_Player == PLAYER_1)
			blue.SetDrawColor(app.renderer);
		else
			red.SetDrawColor(app.renderer);
		switch (piece_type) {
		case PIECE_TRIANGLE:
			draw_triangle(app.renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_CYLINDER:
			draw_diagonal(app.renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_SQUARE:
			draw_square(app.renderer, cell.coord_x + 10, cell.coord_x + 90, cell.coord_y + 10, cell.coord_y + 90);
			break;
		case PIECE_CIRCLE:
			SDL_RenderDrawCircle(app.renderer, cell.coord_x + 50, cell.coord_y + 50, 49);
			break;
		}

	}
	for (int i = 0; i < BOARD_DIM * 2; i++) {
		Cell cell = playerboard2.playerboard[i];
		PieceType piece_type = cell.m_Piece;
		if (cell.m_Player == PLAYER_1)
			blue.SetDrawColor(app.renderer);
		else
			red.SetDrawColor(app.renderer);
		switch (piece_type) {
		case PIECE_TRIANGLE:
			draw_triangle(app.renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_CYLINDER:
			draw_diagonal(app.renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_SQUARE:
			draw_square(app.renderer, cell.coord_x + 10, cell.coord_x + 90, cell.coord_y + 10, cell.coord_y + 90);
			break;
		case PIECE_CIRCLE:
			SDL_RenderDrawCircle(app.renderer, cell.coord_x + 50, cell.coord_y + 50, 49);
			break;
		}

	}
}





