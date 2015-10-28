/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 20:49
* @email	: wdjlost@gmail.com
* @doc		: 控制台显示
*****************************************************************************/
#include<iostream>
using namespace std;

#include"console.h"
#include"model/chessboard.h"

void Console::ShowChessboard(const ChessBoard& chessboard)
{
	int size = chessboard.GetSize();
    for(int y=-1; y<size; ++y)
    {
        for(int x=-1; x<size; ++x)
        {
            if(x == -1 && y == -1)
            {
                //cout << " ♨ ";
				cout << " x ";
				continue;
            }

            if(y == -1)
            {
                if(x < 10)
                    cout << " "<< x << " ";
                else if(x >= 10 && x < 100)
                    cout << x << " ";
                continue;
            }

            if(x == -1)
            {
                if(y < 10)
                    cout << " "<< y << " ";
                else if(y >= 10 && y < 100)
                    cout << y << " ";
                continue;
            }

            switch(chessboard.GetChess(x, y))
            {
                case CT_NULL:
                    //cout << " ┼ ";
					cout << "   ";
					break;
                case CT_WHITE:
                    //cout << " ☻ ";
					cout << " o ";
					break;
                case CT_BLACK:
                    //cout << " ☺ ";
					cout << " # ";
					break;
                default:
                    cout << "  ";
                    break;
            }
        }
        cout<<"\n";
    }
}

void Console::GetNextDown(int& x, int& y)
{
    //cout << "☞  ";
	cout << ">";
	cin >> x >> y;
}

void Console::ShowResult(GameResult result)
{
	cout << " === GAME OVER. ";
	switch (result)
	{
	case GameResult::BLACK_WIN:
		cout << " BLACK WIN" << endl;
		break;
	case GameResult::WHITE_WIN:
		cout << " WHITE WIN" << endl;
		break;
	case GameResult::DRAW:
		cout << " DRAW" << endl;
		break;
	default:
		break;
	}
}

void Console::ShowStatInfo(StatInfo stat)
{
	cout << "--- cost: " << stat.cost_ms << "ms, eval count: " << stat.eval_cnt << " ---" <<endl;
}