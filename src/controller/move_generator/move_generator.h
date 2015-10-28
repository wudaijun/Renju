 // 走法生成器 生成某一棋盘当前所有走法 并保存在指定的层级中
#pragma  once

#include"common/renju.h"

struct Movement
{
    int i;
    int j;
};

class ChessBoard;
class MoveGenerator
{
public:
    static bool CheckValidDown(int i, int j, const ChessBoard& chessboard);

public:
    MoveGenerator();
    // 生成当前棋盘的所有走法 将结果保存在_movements[level][]中 返回走法种数
    int GenAllPossibleMove(const ChessBoard& chessboard, int level);

    Movement GetMovement(int level, int count) const;
	// 走出一步
	bool MakeMove(ChessBoard& chessboard, int level, int count, ChessType chess) const;
	bool MakeMove(ChessBoard& chessboard, Movement move, ChessType chess) const;
	// 退回一步
	bool UnMakeMove(ChessBoard& chessboard, int level, int count) const;

private:
    void addMovement(int i, int j, int level, int count);

private:
    // 保存所有的走法 需要保存深度信息: [depth][count]
    Movement _movements[MAX_DEPTH][CB_MAXSIZE*CB_MAXSIZE];
    int _maxcount;
};
