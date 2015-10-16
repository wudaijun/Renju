#include"gamecontroller.h"
#include"model/chessboard.h"
#include"view/console.h"
#include"controller/move_generator.h"

#include<iostream>
using namespace std;
void GameController::NewGame()
{
    _cur_turn = CT_WHITE;
    if(_chessboard != nullptr)
        _chessboard->Init(CB_WIDTH, CB_HEIGHT);
    else
        _chessboard = new ChessBoard(CB_WIDTH, CB_HEIGHT);

    while(true)
    {
        Console::Display(*_chessboard);
        exchangeTurn();
        yourTurn();
    }
}

void GameController::yourTurn()
{
    int x,  y;
    getNextDown(x, y);
    _chessboard->SetChess(x, y, _cur_turn);
}

void GameController::getNextDown(int& x, int& y)
{
    Console::GetNextDown(x, y);
    if (!MoveGenerator::CheckValidDown(x, y, *_chessboard))
    {
        getNextDown(x, y);
    }
}

void GameController::exchangeTurn()
{
    if(_cur_turn == CT_WHITE)
        _cur_turn = CT_BLACK;
    else if(_cur_turn == CT_BLACK)
        _cur_turn = CT_WHITE;
}
