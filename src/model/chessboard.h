#include"chessboard_def.h"

class ChessBoard
{
public:
    ChessBoard();
    ChessBoard(int width, int height);
    ~ChessBoard();

    bool Init(int width, int height);

    int GetChess(int x, int y) const;
    int SetChess(int x, int y, int chess);
    bool IsChessExist(int x, int y) const;
    bool IsValidPos(int x, int y) const;

    inline int GetWidth() const
    {
        return _width;
    }

    inline int GetHeight() const
    {
        return _height;
    }

private:
    bool createChessBoard(int width, int height);
    void destroyChessBoard();


private:
    int** _chessboard;
    int _width;
    int _height;
};
