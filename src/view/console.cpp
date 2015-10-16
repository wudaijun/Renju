#include<iostream>
using namespace std;

#include"console.h"
#include"model/chessboard.h"

void Console::Display(const ChessBoard& chessboard)
{
    int width = chessboard.GetWidth();
    int height = chessboard.GetHeight();
    for(int y=-1; y<height; ++y)
    {
        for(int x=-1; x<width; ++x)
        {
            if(x == -1 && y == -1)
            {
                cout << " ♨ ";
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
                    cout << " ┼ ";
                    break;
                case CT_WHITE:
                    cout << " ☻ ";
                    break;
                case CT_BLACK:
                    cout << " ☺ ";
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
    cout << "☞  ";
    cin >> x >> y;
}
