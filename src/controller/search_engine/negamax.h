/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 21:05
* @email	: wdjlost@gmail.com
* @doc		: �����㷨��������ֵ�㷨
*****************************************************************************/

#pragma once

#include "search_engine.h"

class NegaMax : public SearchEngine
{
protected:
   bool searchAGoodMove(bool is_white_turn, Movement& bestmove) override;

private:
   int negaMax(int depth, bool is_white_turn);
};
