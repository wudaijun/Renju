#include "common/renju.h"
class ChessBoard;
class Console
{
public:
	// ��ʾ��ǰ���
    static void ShowChessboard(const ChessBoard& chessboard);
	// ��ȡ��������
    static void GetNextDown(int& x, int& y);
	// ��ʾ��Ϸ���
	static void ShowResult(GameResult result);
	// ��ʾͳ������
	static void ShowStatInfo(StatInfo stat);
};
