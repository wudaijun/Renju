/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 20:48
* @email	: wdjlost@gmail.com
* @doc		: 搜索引擎测试 启动后 按回车即可查看搜索引擎相互博弈
*****************************************************************************/
#include<iostream>
using namespace std;

#include "controller/evaluator/evaluator.h"
#include "controller/search_engine/negamax.h"
#include "controller/search_engine/negamax_ab.h"
#include "view/console.h"
int main()
{
	
	Evaluator ev;
	MoveGenerator gen;
	ChessBoard chessboard;
	NegaMax_AB se;
	se.SetSearchDepth(1);
	bool is_white_turn = false;
	Movement move;
	while (true)
	{
		GameResult result = se.IsGameOver(chessboard);
		if (result != GameResult::FIGHTING)
		{
			Console::ShowResult(result);
			break;
		}

		se.SearchAGoodMove(chessboard, is_white_turn, move);
		ChessType chess = is_white_turn ? CT_WHITE : CT_BLACK;
		chessboard.SetChess(move.i, move.j, chess);
		Console::ShowChessboard(chessboard);
		
		getchar();
		is_white_turn = !is_white_turn;
	}
	getchar();

	return 0;
}