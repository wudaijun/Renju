#include<iostream>
using namespace std;

#include"model/chessboard.h"
#include"controller/evaluator/evaluator.h"

#define o CT_WHITE
#define x CT_BLACK
#define _ CT_NULL

ChessType cb[CB_SIZE][CB_SIZE] = {
		{ _, o, o, o, _, o, x, x, _, x, _ },
		{ x, x, x, _, _, _, _, _, o, o, o },
		{ x, x, _, o, o, _, _, x, x, x, _ },
		{ x, o, _, o, o, _, _, _, x, x, _ },
		{ _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _ }
};

int main()
{
	Evaluator ev;
	ChessBoard chessboard(cb);
	int v = ev.Evaluate(chessboard, false);
	ev.PrintTypeRecord();
	cout << "EVAL: " << v << endl;
	getchar();
	return 0;
}
