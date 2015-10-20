#include"evaluator.h"

#include<iostream>
using namespace std;

#define MIN(a, b) (a<b?a:b)

typedef int ChessType;

Evaluator::Evaluator()
{
}

void Evaluator::initPosValue(int size)
{
    // 初始化位置价值表
    // 形如：
    // 0 0 0 0 0 0 0 0 0 0 0
    // 0 1 1 1 1 1 1 1 1 1 0
    // 0 1 2 2 2 2 2 2 2 1 0
    // 0 1 2 3 3 3 3 3 2 1 0
    // 0 1 2 3 4 4 4 3 2 1 0
    // 0 1 2 3 4 5 4 3 2 1 0
    // 0 1 2 3 4 4 4 3 2 1 0
    // 0 1 2 3 3 3 3 3 2 1 0
    // 0 1 2 2 2 2 2 2 2 1 0
    // 0 1 1 1 1 1 1 1 1 1 0
    // 0 0 0 0 0 0 0 0 0 0 0

    // 仅在第一次使用和棋盘改变大小时，重新生成PosValue
    if(_cbsize == size && _posvalue != nullptr)
        return;
    if(_posvalue != nullptr)
    {
        for(int i=0; i<_cbsize; i++)
            delete[] _posvalue[i];
        delete[] _posvalue;
    }
    _posvalue = new int* [_cbsize];
    _cbsize = size;
    for(int i=0; i<_cbsize; i++)
    {
        _posvalue[i] = new int[_cbsize];
        for(int j=0; j<_cbsize; j++)
        {
            int up      = i - 0;
            int down    = _cbsize-1 - i;
            int left    = j - 0;
            int right   = _cbsize-1 - j;
            int posvalue    = MIN(MIN(up,down), MIN(left, right));
            _posvalue[i][j] = posvalue;
        }
    }
}



Evaluator::~Evaluator()
{
    for(int i=0; i<_cbsize; i++)
        delete[] _posvalue[i];
    delete[] _posvalue;
    _posvalue = nullptr;
}

int Evaluator::Evaluate(const ChessBoard& chessboard, bool bIsBlackTurn)
{
    initPosValue(chessboard.GetSize());
    return 1;
}

int Evaluator::analysisHorizon(const ChessBoard& chessboard, int i, int j)
{
    ChessType tmpline[CB_MAXSIZE];
    for(int k=0; k<_cbsize; k++)
        tmpline[k] = chessboard.GetChess(i, k);
    analysisLine(tmpline, size, j);
    for(int k=0; k<_cbsize; k++)
    {
        if(_tmp_record[k] != TOANALYSIS)
            _type_record[i][k][0] = _tmp_record[k];
    }
    return _type_record[i][j][0];
}

int Evaluator::analysisVertical(const ChessBoard& chessboard, int i, int j)
{
    ChessType tmpline[CB_MAXSIZE];
    for(int k=0; k<_cbsize; k++)
        tmpline[k] = chessboard.GetChess(k, j);
    analysisLine(tmpline, _cbsize, i)
    for(int k=0; k<size; k++)
    {
        if(_tmp_record[k] != TOANALYSIS)
            _type_record[k][j][1] = _tmp_record[k];
    }
    return _type_record[i][j][1];
}

int Evaluator::analysisLeftDown(const ChessBoard& chessboard, int i, int j)
{
    ChessType tmpline[CB_MAXSIZE];
    int istart, jstart;
    if(i + j > _cbsize-1)
    {
        istart = _cbsize-1;
        jstart = i+j-_cbsize+1;
    }
    else
    {
        istart = i+j;
        jstart = 0;
    }

    int k;
    for(k=0; k<_cbsize; k++)
    {
        if(jstart+k>_cbsize-1 || istart-k<0)
            break;
        tmpline[k] = chessboard.GetChess(istart-k, jstart+k);
    }
    analysisLine(tmpline, k, j-jstart);
    for(int k=0; k<_cbsize; k++)
    {
        if(_tmp_record[k] != TOANALYSIS)
            _type_record[istart-k][jstart+k][3] = _tmp_record[k];
    }
    return _type_record[i][j][3];
}

int Evaluator::analysisLine(ChessType line[], int size, int pos)
{
    memset(_tmp_record, sizeof(_tmp_record), TOANALYSIS);
    // 小于5格 没有价值 直接标记为分析过
    if(size < 5)
    {
        memset(_tmp_record, ANALYSISED, size);
        return 0;
    }
    ChessType chesstype = line[pos];

    int leftSame, rightSame;
    int leftValid, rightValid;

    // 分析左右相同棋子
    leftSame = rightSame = pos;
    while(leftSame > 0 && line[leftSame-1] == chesstype)
        -- leftSame;
    while(rightSame < size-1 && line[rightSame+1] == chesstype)
        ++ rightSame;

    // 分析左右可下位置
    leftValid = leftSame;
    rightValid = rightSame;
    while(leftValid > 0 && (line[leftValid-1] == CT_NULL || line[leftValid-1] == chesstype))
        -- leftValid;
    while(leftValid < size-1 && (line[rightValid+1] == CT_NULL || line[rightValid+1] == chesstype))
        ++ rightValid;

    int sameCount = rightSame - leftSame + 1;
    int validCount = rightValid - leftValid + 1;
    // 可下位置小于5 没有价值
    if(validCount < 5)
    {
        memset(_tmp_record, ANALYSISED, size);
        return 0;
    }

    // 将所有相连棋子 设为已分析(避免重复计数)
    for(int i=leftSame; i<rightSame; i++)
        _tmp_record[i] = ANALYSISED;

    // 五连
    if(sameCount >= 5)
    {
        _tmp_record[pos] = FIVE;
        return FIVE; // 直接返回
    }
    // 四连
    if(sameCount == 4)
    {
        bool leftClear = false; // 左边是否被堵
        if(leftSame > 0 && line[leftSame-1] == CT_NULL)
            leftClear = true;

        bool rightClear = false;
        if(rightSame < size-1 && line[rightSame+1] == CT_NULL)
            rightClear = true;

        if(leftClear && rightClear) _tmp_record[pos] = FOUR;
        else if(leftClear || rightClear) _tmp_record[pos] = SFOUR;

        return _tmp_record[pos];
    }

    // 三连
    if(sameCount == 3)
    {
        bool leftClear = false;
        if(leftSame > 0)
        {
            if(line[leftSame-1] == CT_NULL)
            {
                if(leftSame > 1 && line[leftSame-2] == line[leftSame])
                {
                    // 参与评判的棋子都要标记
                    _tmp_record[leftSame-2] = ANALYSISED;
                    // 三连的左右评估值分别放在leftSame rightSame上
                    // 以解析 * *** * 这种棋局 这实际上是两个SFOUR
                    _tmp_record[leftSame] = SFOUR; // * ***
                }
                else
                    leftClear = true;
            }
        }

        if(rightSame < size-1)
        {
            if(line[rightSame+1] == CT_NULL)
            {
                if(rightSame < size-2 && line[rightSame+2] == line[rightSame])
                {
                    _tmp_record[rightSame+2] = ANALYSISED;
                    _tmp_record[rightSame] = SFOUR; // *** *
                }
                else
                {
                    if(leftClear)
                        _tmp_record[rightSame] = THREE;
                    else
                        _tmp_record[rightSame] = STHREE;
                }
            }
            else if(leftClear) 
                _tmp_record[rightSame] = STHREE;
        }
        else if(leftClear) _tmp_record[rightSame] = STHREE;

        if(_tmp_record[leftSame]==SFOUR || _tmp_record[rightSame] == SFOUR)
            return SFOUR;
        else return _tmp_record[rightSame];
    }

    // 两连
    if(sameCount == 2)
    {
        bool leftClear = false;
        if(leftSame>0 && line[leftSame-1] == CT_NULL) // +00
        {
            if(leftSame>1 && line[leftSame-2] == line[leftSame]) // 0+00
            {
                if(leftSame>2)
                {
                    if(line[leftSame-3] == line[leftSame]) // 00+00
                    {
                        _tmp_record[leftSame-2] = ANALYSISED;
                        _tmp_record[leftSame-3] = ANALYSISED;
                        _tmp_record[leftSame] = SFOUR;
                    }
                    else if(line[leftSame-3] == CT_NULL)
                    {
                        _tmp_record[leftSame-2] = ANALYSISED;
                        _tmp_record[leftSame] = STHREE;
                    }
                }
            }
            else
            {
                // TODO 0++00
                leftClear = true;
            }
        }

        if(rightSame < size-1 && line[rightSame+1] == CT_NULL) // 00+
        {
            if(rightSame < size-2 && line[rightSame+2] == line[rightSame]) // 00+0
            {
                if(rightSame < size-3)
                {
                    if(line[rightSame+3] == line[rightSame]) // 00+00
                    {
                        _tmp_record[rightSame+2] = ANALYSISED;
                        _tmp_record[rightSame+3] = ANALYSISED;
                        _tmp_record[rightSame] = SFOUR;
                    }
                    else if(line[rightSame+3] == CT_NULL) // 00+0+
                    {
                        _tmp_record[leftSame+2] = ANALYSISED;
                        _tmp_record[leftSame] = STHREE;
                    }
                }
            }
            else
            {
                if(leftClear)
                    _tmp_record[rightSame] = TWO;
            }
        }
        else if(leftClear)
            _tmp_record[rightSame] = STWO;

        if(_tmp_record[leftSame] == SFOUR || _tmp_record[rightSame] == SFOUR)
            return SFOUR;
        if(_tmp_record[leftSame] == STHREE || _tmp_record[rightSame] == STHREE)
            return STHREE;
        return _tmp_record[rightSame];
    }
    return _tmp_record[pos];
}

int test_line(int line[], int size, int pos)
{
    analysisLine(line, size, pos);
    for(int i=0; i<size; i++)
        cout << line[i];
    cout << endl;
}
