#include"game_controller.h"
#include"view/console.h"
#include"controller/move_generator/move_generator.h"
#include "controller/search_engine/negamax_ab.h"

#include<iostream>
using namespace std;

GameController::GameController()
{
	_engine = new NegaMax_AB();
}

GameController::~GameController()
{
// 	if (_engine != nullptr)
// 		delete _engine;
}

void GameController::NewGame()
{
    _cur_turn = CT_BLACK;
	GameResult result = FIGHTING;
    while(true)
    {
		
		Console::ShowChessboard(_chessboard);
		if (result = _engine->IsGameOver(_chessboard))
			break;
        yourTurn();
		exchangeTurn();
		

		Console::ShowChessboard(_chessboard);
		StatInfo stat;
		if (result = _engine->IsGameOver(_chessboard))
			break;
		engineTurn(&stat);
		Console::ShowStatInfo(stat);
		exchangeTurn();
    }

	GameOver(result);
}

void GameController::GameOver(GameResult result)
{
	Console::ShowResult(result);
}

void GameController::yourTurn()
{
    int i, j;
    getNextDown(i, j);
    _chessboard.SetChess(i, j, _cur_turn);
}

void GameController::engineTurn(StatInfo* stat/* = nullptr*/)
{
	Movement m;
	if (_engine->SearchAGoodMove(_chessboard, _cur_turn == CT_WHITE, m, stat))
		_chessboard.SetChess(m.i, m.j, _cur_turn);
}

void GameController::getNextDown(int& i, int& j)
{
    Console::GetNextDown(i, j);
    if (!MoveGenerator::CheckValidDown(i, j, _chessboard))
    {
        getNextDown(i, j);
    }
}

void GameController::exchangeTurn()
{
    if(_cur_turn == CT_WHITE)
        _cur_turn = CT_BLACK;
    else if(_cur_turn == CT_BLACK)
        _cur_turn = CT_WHITE;
}
