/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 21:51
* @email	: wdjlost@gmail.com
* @doc		: 估值核心 
*****************************************************************************/
#pragma once

#include "common/renju.h"

#define TOANALYSIS  0
#define STWO        1
#define STHREE      2
#define SFOUR       3
#define TWO         4
#define THREE       5
#define FOUR        6
#define DTHREE      7
#define FOURTHREE   8
#define DFOUR       9
#define FIVE        10
#define UNKNOWN     11
#define ANALYSISED  13
#define TYPE_MAX    20

// 定义四个方向
#define HORIZON		0
#define VERTICAL	1
#define LEFTUP		2
#define LEFTDOWN	3

#define EVAL_MAX 9999

typedef char AnalysisType;

// 估值核心 对当前棋局进行估值
class ChessBoard;
class Evaluator
{
public:
    Evaluator();
    ~Evaluator();

public:
    int Evaluate(const ChessBoard& chessboard, bool isWhiteTurn);
	bool IsGameOver(const ChessBoard& chessboard, bool isWhiteTurn, int& eval);

public:
	// 统计信息
	void ResetCallCounter()	{ _call_counter = 0; }
	int  GetCallCounter() { return _call_counter; }

public:
	// 调试接口
	void PrintTypeRecord();

private:
	// 水平方向
    int analysisHorizon(const ChessBoard& chessboard, int i, int j);
	// 竖直方向
    int analysisVertical(const ChessBoard& chessboard, int i, int j);
	// 左下 -> 右上方向
    int analysisLeftDown(const ChessBoard& chessboard, int i, int j);
	// 左上 -> 右下方向
    int analysisLeftUp(const ChessBoard& chessboard, int i, int j);
    int analysisLine(ChessType line[], int size, int pos);
    void initPosValue(int size);
private:
    // 棋盘大小
    int _cbsize = 0;
    // 位置价值
    int** _posvalue = nullptr;
    // 棋盘所有棋子各个方向上的类型
    AnalysisType _type_record[CB_MAXSIZE][CB_MAXSIZE][4];
    // 棋盘白棋黑棋所有类型数量统计
    int _type_count_black[TYPE_MAX];
	int _type_count_white[TYPE_MAX];
    // 临时保存当前行的分析结果
    AnalysisType _tmp_record[CB_MAXSIZE];

	int _call_counter = 0;
};
