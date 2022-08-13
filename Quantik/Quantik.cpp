#include <iostream>
#include <string>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Board.h"
#include "App.h"
#include "Color.h"
#include "ctime"

/*Player* other_player(Player* pPlayerboard) {
    if (pPlayerboard == &player1)
        return &player2;
    else
        return &player1;
}*/

int main(int argc, char* argv[])
{   
    std::srand(std::time(nullptr));
    app.initSDL();
    app.board.mapping();
    app.player1.player_type = PLAYER_1;
    app.player2.player_type = PLAYER_2;
    app.player1.Player_board_init();
    app.player2.Player_board_init();
    app.player1.player_mapping_1();
    app.player2.player_mapping_2();
    app.player2.SetAI(true);
    do
    {
        black.SetDrawColor(app.renderer);
        SDL_RenderClear(app.renderer);
        app.draw();
        app.doInput();
        app.Hilight(app.player1, app.board);
        app.Hilight(app.player2, app.board);
        SDL_RenderPresent(app.renderer);
    }
    while (app.victory == 0);
    switch (app.victory)
    {
    case -1:
        printf("Draw\n");
        break;
    case 0:
        printf("Should never happen\n");
        break;
    case 1:
        printf("Victory Player 1\n");
        break;
    case 2:
        printf("Victory Player 2\n");
        break;
    }

}