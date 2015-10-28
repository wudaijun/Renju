/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 22:04
* @email	: wdjlost@gmail.com
* @doc		: 搜索算法：负极大值 + Alpha-Beta剪枝
*****************************************************************************/

#pragma once

#include "search_engine.h"

class NegaMax_AB : public SearchEngine
{
public:
	bool searchAGoodMove(bool is_white_turn, Movement& bestmove) override;

private:
	int negaMax_AB(int depth, bool is_white_turn, int alpha, int beta);
};