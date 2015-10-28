#include"move_generator.h"
#include "model/chessboard.h"
#include <assert.h>

MoveGenerator::MoveGenerator()
{
}

bool MoveGenerator::CheckValidDown(int i, int j, const ChessBoard& chessboard)
{
    return chessboard.IsValidPos(i, j) && !chessboard.IsChessExist(i, j);
}

int MoveGenerator::GenAllPossibleMove(const ChessBoard& chessboard, int level)
{
	int size = chessboard.GetSize();
    int count = 0;
    for(int i=0; i<size; ++i)
    {
        for(int j=0; j<size; ++j)
        {
            if(CheckValidDown(i, j, chessboard))
            {
                addMovement(i, j, level, count++);
            }
        }
    }
    return count;
}

void MoveGenerator::addMovement(int i, int j, int level, int count)
{
    assert(0<=level&&level<MAX_DEPTH && 0<=count&&count<CB_MAXSIZE*CB_MAXSIZE);
    Movement move;
    move.i = i;
    move.j = j;
    _movements[level][count] = move;
}

Movement MoveGenerator::GetMovement(int level, int count) const 
{
    assert(0<=level&&level<MAX_DEPTH && 0<=count&&count<CB_MAXSIZE*CB_MAXSIZE);
    return _movements[level][count];
}

bool MoveGenerator::MakeMove(ChessBoard& chessboard, int level, int count, ChessType chess) const 
{
	Movement move = _movements[level][count];
	return CT_NULL == chessboard.SetChess(move.i, move.j, chess);

}

bool MoveGenerator::MakeMove(ChessBoard& chessboard, Movement move, ChessType chess) const 
{
	return CT_NULL == chessboard.SetChess(move.i, move.j, chess);
}

bool MoveGenerator::UnMakeMove(ChessBoard& chessboard, int level, int count) const 
{
	Movement move = _movements[level][count];
	return CT_NULL != chessboard.SetChess(move.i, move.j, CT_NULL);
}