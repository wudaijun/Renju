/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 20:50
* @email	: wdjlost@gmail.com
* @doc		: 搜索引擎基类 挂载走法生成器，估值核心等
*****************************************************************************/
#pragma once

#include "model/chessboard.h"
#include "common/renju.h"
#include "controller/move_generator/move_generator.h"
#include "controller/evaluator/evaluator.h"

class SearchEngine
{
public:
	SearchEngine();
	~SearchEngine();

public:
    void SetSearchDepth(int depth){ _search_depth = depth > MAX_DEPTH ? MAX_DEPTH : depth; }

public:
	GameResult IsGameOver(const ChessBoard& chessboard);
	bool SearchAGoodMove(ChessBoard& chessboard, bool is_white_turn, Movement& bestmove, StatInfo* stat = nullptr);

protected:
    virtual bool searchAGoodMove(bool is_white_turn, Movement& bestmove) = 0;


protected:
    ChessBoard _chessboard;
    int _search_depth;
    Evaluator _evaluator;
    MoveGenerator _move_generator;
	Movement _bestmove;
};
