#pragma once
#include"common/renju.h"

class ChessBoard
{
public:
    ChessBoard();
    ChessBoard(int size);
	ChessBoard(ChessType cb[CB_SIZE][CB_SIZE]);
    ~ChessBoard();

	// 以行列(i,j)进行索引
    ChessType GetChess(int i, int j) const;
    ChessType SetChess(int i, int j, ChessType chess);
    bool IsChessExist(int i, int j) const;
    bool IsValidPos(int i, int j) const;
	bool IsFull() const ; // 棋盘是否已满

	inline int GetSize() const { return _size; }

private:
    bool clearChessBoard();

private:
    ChessType _chessboard[CB_MAXSIZE][CB_MAXSIZE];
	int _size;
};
