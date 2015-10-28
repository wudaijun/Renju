#include"ChessBoard.h"

ChessBoard::ChessBoard()
{
	_size = CB_SIZE;
	clearChessBoard();
}

ChessBoard::ChessBoard(int size)
{
	_size = size;
	clearChessBoard();
}

ChessBoard::ChessBoard(ChessType cb[CB_SIZE][CB_SIZE])
{
	_size = CB_SIZE;
	for (int i = 0; i < CB_SIZE; i++)
		for (int j = 0; j < CB_SIZE; j++)
			_chessboard[i][j] = cb[i][j];
}

ChessBoard::~ChessBoard()
{
}

ChessType ChessBoard::GetChess(int i, int j) const
{
    if(_chessboard!=nullptr && IsValidPos(i, j))
        return _chessboard[i][j];
    return CT_NULL;
}

// 落子 返回该位置上之前的棋子
ChessType ChessBoard::SetChess(int i, int j, ChessType chess)
{
    int oldchess = _chessboard[i][j];
    _chessboard[i][j] = chess;
    return oldchess;
}

bool ChessBoard::IsChessExist(int i, int j) const
{
    return _chessboard[i][j] != CT_NULL;
}

bool ChessBoard::IsValidPos(int i, int j) const
{
    if(0<=j && j<_size && 0<=i && i<_size)
    {
        return true;
    }
    return false;
}

bool ChessBoard::IsFull() const
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			if (_chessboard[i][j] == CT_NULL)
				return false;

	return true;
}

bool ChessBoard::clearChessBoard()
{
	for (int i = 0; i < CB_MAXSIZE; i++)
		for (int j = 0; j < CB_MAXSIZE; j++)
			_chessboard[i][j] = CT_NULL;

	return true;
}


