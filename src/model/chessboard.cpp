#include"chessboard.h"

ChessBoard::ChessBoard()
{
    _chessboard = nullptr;
    _width = 0;
    _height = 0;
}

ChessBoard::ChessBoard(int width, int height)
{
    createChessBoard(width, height);
}

ChessBoard::~ChessBoard()
{
    destroyChessBoard();
}

bool ChessBoard::Init(int width, int height)
{
    if(width <= 0 || height <= 0)
        return false;

    destroyChessBoard();
    return createChessBoard(width, height);
}

int ChessBoard::GetChess(int x, int y) const
{
    if(_chessboard!=nullptr && IsValidPos(x, y))
        return _chessboard[y][x];
    return CT_NULL;
}

// 落子 并不检查该位置是否已经存在棋子 这是Controller该关心的
// 模型本身原则上只负责简单读写
int ChessBoard::SetChess(int x, int y, int chess)
{
    int oldchess = _chessboard[y][x];
    _chessboard[y][x] = chess;
    return oldchess;
}

bool ChessBoard::IsChessExist(int x, int y) const
{
    return _chessboard[y][x] != CT_NULL;
}

bool ChessBoard::IsValidPos(int x, int y) const
{
    if(0<=x && x<_width && 0<=y && y<_height)
    {
        return true;
    }
    return false;
}

bool ChessBoard::createChessBoard(int width, int height)
{
    _width = width;
    _height = height;

    _chessboard = new int*[_height];
    for(int i=0; i<_height; ++i)
    {
        _chessboard[i] = new int[_width];
        for(int j=0; j<_width; ++j)
            _chessboard[i][j] = CT_NULL;
    }
    _chessboard[2][2] = CT_BLACK;
    _chessboard[3][3] = CT_WHITE;
    return true;
}

void ChessBoard::destroyChessBoard()
{
    if(_chessboard != nullptr)
    {
        for(int i=0; i<_height; ++i)
        {
            delete[] _chessboard[i];
        }
        delete[] _chessboard;
        _chessboard = nullptr;
    }
}


