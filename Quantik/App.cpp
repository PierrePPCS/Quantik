#include "App.h"
#include "Color.h"
#include "Utils.h"

APP::APP()
{
	dragged_source_cell = -1;
	playerboard1.SetBoard(&board);
	playerboard2.SetBoard(&board);
}

bool APP::check_victory(int i, int j)
{
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

void draw_highlight(const Cell& C, const APP& app)
{
	green.SetDrawColor(app.renderer);
	switch (C.m_Piece)
	{
	case PIECE_SQUARE:
		draw_square(app.renderer, C.coord_x, C.coord_x + 100, C.coord_y, C.coord_y + 100);
		break;
	case PIECE_CIRCLE:
		draw_circle(app.renderer, C.coord_x + 50, C.coord_y + 50, 50);
		break;
	case PIECE_CYLINDER:
		draw_diagonal(app.renderer, C.coord_x, C.coord_x + 100, C.coord_y, C.coord_y + 100);
		break;
	case PIECE_TRIANGLE:
		draw_triangle(app.renderer, C.coord_x, C.coord_x + 100, C.coord_y, C.coord_y + 100);
		break;
	}
}

void APP::Hilight(const Player& player_board, const Board& board)
{
	int x = 0;
	int y = 0;
	int boutons = SDL_GetMouseState(&x, &y);
	int icell = 0;
	if (player_board.is_in_playerboard(x, y, icell))
	{

		const Cell& C = player_board.playerboard[icell];
		draw_highlight(C, *this);

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

	if (current_playerboard().IsAI())
	{
		if (!current_playerboard().ai->play_dumb())
			printf("L'IA ne peut pas jouer !!!\n");
		other_player();
		return;
	}
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
				if (current_playerboard().is_in_playerboard(mouse_x, mouse_y, cell) && current_playerboard().playerboard[cell].m_Piece != PIECE_NONE)
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
					if (board.is_available(i, j, dragged_piece, current_player))
					{
						board.change_cell(i, j, current_playerboard().playerboard[dragged_source_cell].m_Piece, current_player);
						current_playerboard().playerboard[dragged_source_cell].m_Piece = PIECE_NONE;
						dragged_source_cell = -1;
						if (check_victory(i, j))
							printf("v");
						other_player();
					}
				}
				PieceType pice;
				int k;
				int l;
				if (soon_to_win(pice, k, l, PLAYER_1))
					printf("Bient�t gagn�");
			}
			break;
		}
	}
}


void APP::draw()
{
	white.SetDrawColor(renderer);
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
				blue.SetDrawColor(renderer);
			else
				red.SetDrawColor(renderer);
			switch (piece_type) {

			case PIECE_TRIANGLE:
				draw_triangle(renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y - 100, cell.coord_y);
				break;
			case PIECE_CYLINDER:
				draw_diagonal(renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y - 100, cell.coord_y);
				break;
			case PIECE_SQUARE:
				draw_square(renderer, cell.coord_x + 10, cell.coord_x + 90, cell.coord_y - 90, cell.coord_y - 10);
				break;
			case PIECE_CIRCLE:
				draw_circle(renderer, cell.coord_x + 50, cell.coord_y - 50, 49);
				break;

			}
		}
	}
	for (int i = 0; i < BOARD_DIM * 2; i++) {
		Cell cell = playerboard1.playerboard[i];
		PieceType piece_type = cell.m_Piece;
		if (cell.m_Player == PLAYER_1)
			blue.SetDrawColor(renderer);
		else
			red.SetDrawColor(renderer);
		switch (piece_type) {
		case PIECE_TRIANGLE:
			draw_triangle(renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_CYLINDER:
			draw_diagonal(renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_SQUARE:
			draw_square(renderer, cell.coord_x + 10, cell.coord_x + 90, cell.coord_y + 10, cell.coord_y + 90);
			break;
		case PIECE_CIRCLE:
			draw_circle(renderer, cell.coord_x + 50, cell.coord_y + 50, 49);
			break;
		}

	}
	for (int i = 0; i < BOARD_DIM * 2; i++) {
		Cell cell = playerboard2.playerboard[i];
		PieceType piece_type = cell.m_Piece;
		if (cell.m_Player == PLAYER_1)
			blue.SetDrawColor(renderer);
		else
			red.SetDrawColor(renderer);
		switch (piece_type) {
		case PIECE_TRIANGLE:
			draw_triangle(renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_CYLINDER:
			draw_diagonal(renderer, cell.coord_x, cell.coord_x + 100, cell.coord_y, cell.coord_y + 100);
			break;
		case PIECE_SQUARE:
			draw_square(renderer, cell.coord_x + 10, cell.coord_x + 90, cell.coord_y + 10, cell.coord_y + 90);
			break;
		case PIECE_CIRCLE:
			draw_circle(renderer, cell.coord_x + 50, cell.coord_y + 50, 49);
			break;
		}

	}
}


bool APP::soon_to_win(PieceType& final_piece, int& i, int& j, PlayerType current_player)
{
	std::vector<CoordType> available;
	board.available_cells(playerboard2, available);
	int k = available.size();
	for (int _i = 0; _i < k; _i++) {
		std::vector<Cell> Line;
		std::vector<Cell> Column;
		std::vector<Cell> Square;
		PieceType piece_type = available[_i].piece_type;
		board.GetLine(available[_i].i, Line);
		board.GetColumn(available[_i].j, Column);
		board.GetSquare(available[_i].j, available[_i].j, Square);
		suppr(Line, piece_type, current_player);
		suppr(Column, piece_type, current_player);
		suppr(Square, piece_type, current_player);
		if (Line.size() == 1) {
			i = available[_i].i;
			j = available[_i].j;
			final_piece = Line[0].m_Piece;
			return true;
		}
		if (Column.size() == 1) {
			i = available[_i].i;
			j = available[_i].j;
			final_piece = Column[0].m_Piece;
			return true;
		}
		if (Square.size() == 1) {
			i = available[_i].i;
			j = available[_i].j;
			final_piece = Square[0].m_Piece;
			return true;
		}
	}
	return false;
}



