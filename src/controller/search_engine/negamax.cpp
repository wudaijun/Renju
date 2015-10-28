#include "negamax.h"
#include <assert.h>

bool NegaMax::searchAGoodMove(bool is_white_turn, Movement& bestmove)
{
    negaMax(_search_depth, is_white_turn);
	bestmove = _bestmove;
	return true;
}

int NegaMax::negaMax(int depth, bool is_white_turn)
{
    int score = -EVAL_MAX;
    int maxscore = -EVAL_MAX;
	// 叶子节点  评估返回
    if(depth <= 0)
        return _evaluator.Evaluate(_chessboard, is_white_turn);

	// 非叶子节点 游戏结束 返回评估值
	if (_evaluator.IsGameOver(_chessboard, is_white_turn, score))
		return score;
	ChessType cur_chess = is_white_turn ? CT_WHITE : CT_BLACK;
    int count = _move_generator.GenAllPossibleMove(_chessboard, depth);
    for (int i=0; i<count; i++)
    {
        assert(_move_generator.MakeMove(_chessboard, depth, i, cur_chess));
        score = -negaMax(depth-1, !is_white_turn);
        if(score > maxscore)
        {
            maxscore = score;
            if(depth == _search_depth)
                _bestmove = _move_generator.GetMovement(depth, i);
        }
        assert(_move_generator.UnMakeMove(_chessboard, depth, i));
    }
	return maxscore;
}
