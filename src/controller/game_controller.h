/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/24 10:45
* @email	: wdjlost@gmail.com
* @doc		: 游戏控制器 控制游戏规则
*****************************************************************************/
#include"model/chessboard.h"

class SearchEngine;
class GameController
{
public:
	GameController();
	GameController(const GameController& gamecontroller) = delete;
	GameController& operator = (const GameController&) = delete;
	~GameController();

public:
    void NewGame();

private:
    void yourTurn();
	void engineTurn(StatInfo* stat=nullptr);
    void getNextDown(int &i, int &j);
    void inline exchangeTurn();
	void GameOver(GameResult result);

private:
    ChessBoard _chessboard;
    ChessType _cur_turn;
	SearchEngine* _engine = nullptr;
};
