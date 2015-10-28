#include <assert.h>
#include "negamax_ab.h"

bool NegaMax_AB::searchAGoodMove(bool is_white_turn, Movement& bestmove)
{
	int alpha = -EVAL_MAX;
	int beta = EVAL_MAX;
	negaMax_AB(_search_depth, is_white_turn, alpha, beta);
	bestmove = _bestmove;
	return true;
}

int NegaMax_AB::negaMax_AB(int depth, bool is_white_turn, int alpha, int beta)
{
	int score;
	// 叶子节点  评估返回
	if (depth <= 0)
		return _evaluator.Evaluate(_chessboard, is_white_turn);

	// 非叶子节点 游戏结束 返回评估值
	if (_evaluator.IsGameOver(_chessboard, is_white_turn, score))
		return score;
	ChessType cur_chess = is_white_turn ? CT_WHITE : CT_BLACK;
	int count = _move_generator.GenAllPossibleMove(_chessboard, depth);
	for (int i = 0; i < count; i++)
	{
		assert(_move_generator.MakeMove(_chessboard, depth, i, cur_chess));
		score = -negaMax_AB(depth - 1, !is_white_turn, -beta, -alpha); // 翻转 alpha beta
		assert(_move_generator.UnMakeMove(_chessboard, depth, i));
		if (score > alpha)
		{
			alpha = score;
			if (depth == _search_depth)
				_bestmove = _move_generator.GetMovement(depth, i);
		}
		if (alpha > beta)
			break; // 剪枝 不再搜索后续兄弟节点
	}
	return alpha;
}