#include "search_engine.h"
#include <time.h>

SearchEngine::SearchEngine()
{
	_search_depth = DEFAULT_DEPTH;
}


SearchEngine::~SearchEngine()
{
}

bool SearchEngine::SearchAGoodMove(ChessBoard& chessboard, bool is_white_turn, Movement& bestmove, StatInfo* stat)
{
	auto clock_start = clock();

	_chessboard = chessboard;
	_evaluator.ResetCallCounter();
	bool ret = searchAGoodMove(is_white_turn, bestmove);

	auto clock_end = clock();
	unsigned int cost = (unsigned int)(clock_end - clock_start);
	if (stat != nullptr)
	{
		stat->cost_ms = cost;
		stat->eval_cnt = _evaluator.GetCallCounter();
	}
	return ret;
}

GameResult SearchEngine::IsGameOver(const ChessBoard& _chessboard)
{
	int score;
	if (_evaluator.IsGameOver(_chessboard, true, score))
	{
		if (score > 0)
			return GameResult::WHITE_WIN;
		else
			return GameResult::BLACK_WIN;
	}

	if (_chessboard.IsFull())
		return GameResult::DRAW;

	return FIGHTING;
}
