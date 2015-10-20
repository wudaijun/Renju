#pragma once

#include "model/chessboard_def.h"

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
#define TOANALYSIS  12
#define ANALYSISED  13
#define TYPE_MAX    20

typedef char AnalysisType;

// 估值核心 对当前棋局进行估值
class ChessBoard;
class Evaluator
{
public:
    Evaluator();
    ~Evaluator();
    int Evaluate(const ChessBoard& chessboard, bool bIsBlackTurn);

    // TEST
public:
    int test_line(int line[], int size, int pos);
private:
    int analysisHorizon(const ChessBoard& chessboard, int i, int j);
    int analysisVertical(const ChessBoard& chessboard, int i, int j);
    int analysisLeftDown(const ChessBoard& chessboard, int i, int j);
    int analysisLeftUp(const ChessBoard& chessboard, int i, int j);
    int analysisLine(int line[], int size, int pos);
    void initPosValue(int size);
private:
    // 棋盘大小
    int _cbsize = 0;
    // 位置价值
    int** _posvalue = nullptr;
    // 棋盘所有棋子各个方向上的类型
    AnalysisType _type_record[CB_MAXSIZE][CB_MAXSIZE][4];
    // 棋盘白棋黑棋所有类型数量统计
    int _type_count[2][TYPE_MAX];
    // 临时保存当前行的分析结果
    AnalysisType _tmp_record[CB_MAXSIZE];
};
