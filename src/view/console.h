#include "common/renju.h"
class ChessBoard;
class Console
{
public:
	// 显示当前棋局
    static void ShowChessboard(const ChessBoard& chessboard);
	// 获取玩家落棋点
    static void GetNextDown(int& x, int& y);
	// 显示游戏结果
	static void ShowResult(GameResult result);
	// 显示统计数据
	static void ShowStatInfo(StatInfo stat);
};
