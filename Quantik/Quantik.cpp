#include <iostream>
#include <string>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Board.h"
#include "init.h"
#include "ctime"

/*Player_board* other_player(Player_board* pPlayerboard) {
    if (pPlayerboard == &playerboard1)
        return &playerboard2;
    else
        return &playerboard1;
}*/

int main(int argc, char* argv[])
{
    AI ai;
    std::srand(std::time(nullptr));
    app.initSDL();
    app.board.mapping();
    app.playerboard1.player_type = PLAYER_1;
    app.playerboard2.player_type = PLAYER_2;
    app.playerboard1.Player_board_init();
    app.playerboard2.Player_board_init();
    app.playerboard1.player_mapping_1();
    app.playerboard2.player_mapping_2();
    ai.player_type = PLAYER_1;
    ai.board = app.board;
    do
    {
        black.SetDrawColor(app.renderer);
        SDL_RenderClear(app.renderer);
        app.draw();
        app.doInput();
        app.Hilight(app.playerboard1, app.board);
        app.Hilight(app.playerboard2, app.board);
        SDL_RenderPresent(app.renderer);
    } while (true);
}