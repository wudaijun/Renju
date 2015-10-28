#include "model/chessboard.h"
#include "view/console.h"
#include "controller/game_controller.h"

int main()
{
    GameController gamecontroller;
    gamecontroller.NewGame();
    return 0;
}
