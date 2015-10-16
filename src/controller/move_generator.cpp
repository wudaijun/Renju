#include"move_generator.h"
#include "model/chessboard.h"
#include <assert.h>

MoveGenerator::MoveGenerator(int search_depth, int chessboard_width, int chessboard_height)
{
    // 一个五子棋局，最多可能的走法(当棋盘为空时)
    _maxcount = chessboard_width * chessboard_height;
    _depth = search_depth;
    _movements = new Movement*[search_depth];
    for(int i=0; i<search_depth; ++i)
        _movements[i] = new Movement[_maxcount];
}

bool MoveGenerator::CheckValidDown(int x, int y, const ChessBoard& chessboard)
{
    return chessboard.IsValidPos(x, y) && !chessboard.IsChessExist(x, y);
}

int MoveGenerator::GenAllPossibleMove(const ChessBoard& chessboard, int level)
{
    int width = chessboard.GetWidth();
    int height = chessboard.GetHeight();
    int count = 0;
    for(int y=0; y<height; ++y)
    {
        for(int x=0; x<width; ++x)
        {
            if(CheckValidDown(x, y, chessboard))
            {
                addMovement(x, y, level, count++);
            }
        }
    }
    return count+1;
}

void MoveGenerator::addMovement(int x, int y, int level, int count)
{
    assert(0<=level&&level<_depth && 0<=count&&count<_maxcount);
    Movement move;
    move.x = x;
    move.y = y;
    _movements[level][count] = move;
}

Movement MoveGenerator::GetMovement(int level, int count)
{
    assert(0<=level&&level<_depth && 0<=count&&count<_maxcount);
    return _movements[level][count];
}
