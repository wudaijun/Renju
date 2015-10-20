#include<iostream>
using namespace std;

#include"model/chessboard_def.h"
#include"controller/evaluator.h"

int main()
{
    Evaluator ev(11);
    int line[] = {0,0,1,1,1,0,1};
    ev.analysisLine(line, sizeof(line), 3);
    return 0;
}
