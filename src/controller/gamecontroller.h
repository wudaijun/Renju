
class ChessBoard;
class GameController
{
public:
    void NewGame();

private:
    void yourTurn();
    void getNextDown(int &x, int &y);
    void inline exchangeTurn();

private:
    ChessBoard* _chessboard = nullptr;
    int _cur_turn;
};
