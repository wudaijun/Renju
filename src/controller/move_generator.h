/*
 * author: wudaijun
 * email: wdjlost@gmail.com
 * date: 2015-10-15
 * doc: 走法生成器 生成某一棋盘当前所有走法 并保存在指定的层级中
 */
#define MAX_DEPTH 5

struct Movement
{
    int x;
    int y;
};

class ChessBoard;
class MoveGenerator
{
public:
    static bool CheckValidDown(int x, int y, const ChessBoard& chessboard);

public:
    MoveGenerator(int search_depth, int chessboard_width, int chessboard_height);
    // 生成当前棋盘的所有走法 将结果保存在_movements[level][]中 返回走法种数
    int GenAllPossibleMove(const ChessBoard& chessboard, int level);

    Movement GetMovement(int level, int count);

private:
    void addMovement(int x, int y, int level, int count);

private:
    // 保存所有的走法 需要保存深度信息: [depth][count]
    Movement** _movements;
    int _depth;
    int _maxcount;
};
