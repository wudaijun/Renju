#include<string.h> // for memset
#include <cmath> // for abs
#include"Evaluator.h"
#include "model/chessboard.h"


#define MIN(a, b) ((a)<(b)?(a):(b))

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

	_cbsize = size;
    _posvalue = new int* [_cbsize];
	
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

bool Evaluator::IsGameOver(const ChessBoard& chessboard, bool isWhiteTurn, int& eval)
{
	eval = Evaluate(chessboard, isWhiteTurn);
	if (std::abs(eval) == EVAL_MAX)
		return true;
	return false;
}

// 估值核心 对当前棋局进行估值 估值相对于当前该走的一方
int Evaluator::Evaluate(const ChessBoard& chessboard, bool isWhiteTurn)
{
	++_call_counter;

    initPosValue(chessboard.GetSize());
	memset(_type_record, TOANALYSIS, sizeof(_type_record));
	memset(_type_count_white, 0, sizeof(_type_count_white));
	memset(_type_count_black, 0, sizeof(_type_count_black));

	for (int i = 0; i < _cbsize; i++)
		for (int j = 0; j < _cbsize; j++)
		{
			if (chessboard.GetChess(i, j) != CT_NULL)
			{
				if (_type_record[i][j][HORIZON] == TOANALYSIS)
					analysisHorizon(chessboard, i, j);
				if (_type_record[i][j][VERTICAL] == TOANALYSIS)
					analysisVertical(chessboard, i, j);
				if (_type_record[i][j][LEFTDOWN] == TOANALYSIS)
					analysisLeftDown(chessboard, i, j);
				if (_type_record[i][j][LEFTUP] == TOANALYSIS)
					analysisLeftUp(chessboard, i, j);
			}
		}

	// 结果统计
	for (int i = 0; i < _cbsize; i++)
		for (int j = 0; j < _cbsize; j++)
			for (int k = 0; k < 4; k++) // 四个方向 TODO
			{
				ChessType chesstype = chessboard.GetChess(i, j);
				AnalysisType analytype = _type_record[i][j][k];
				if (chesstype == CT_BLACK)
					_type_count_black[analytype] ++;
				else if (chesstype == CT_WHITE)
					_type_count_white[analytype] ++;
			}

	// 估值
	if (isWhiteTurn)
	{
		if (_type_count_black[FIVE])
			return -EVAL_MAX;
		if (_type_count_white[FIVE])
			return EVAL_MAX;
	}
	else 
	{
		if (_type_count_black[FIVE] > 0)
			return EVAL_MAX;
		if (_type_count_white[FIVE] > 0)
			return -EVAL_MAX;
	}

	// 两个眠四相当于一个活四
	if (_type_count_black[SFOUR] > 1)
		_type_count_black[FOUR] ++;
	if (_type_count_white[SFOUR] > 1)
		_type_count_white[FOUR] ++;

	int white_value = 0;
	int black_value = 0;
	if (isWhiteTurn) // 该白棋走
	{
		// 活四或眠四 均可一步制胜
		if (_type_count_white[FOUR] > 0)
			return 9990;
		if (_type_count_white[SFOUR] > 0)
			return 9980;
		// 此时白棋无四
		// 黑棋活四 必胜
		if (_type_count_black[FOUR] > 0)
			return -9970;
		// 黑棋眠四活三 必胜(未考虑白棋堵四，同时出现白四的情况)
		if (_type_count_black[SFOUR] > 0 && _type_count_black[THREE] > 0)
			return -9960;
		// 黑棋无四 而白棋活三  必胜
		if (_type_count_white[THREE] > 0 && _type_count_black[SFOUR] > 0)
			return 9950;
		// 黑棋有多个活三 而白棋无四三 必胜
		if (_type_count_black[THREE] > 1
			&& _type_count_white[THREE] == 0
			&& _type_count_white[STHREE] == 0)
			return -9940;

		// 接下来不是必胜局  进行加分比较
		// 活三加分
		if (_type_count_white[THREE] > 1)
			white_value += 2000;
		else if (_type_count_white[THREE] == 1)
			white_value += 200;

		if (_type_count_black[THREE] > 1)
			black_value += 500;
		else if (_type_count_black[THREE] == 1)
			black_value += 100;

		// 眠三加分
		white_value += _type_count_white[STHREE] * 20;
		black_value += _type_count_black[STHREE] * 20;

		// 活二加分
		white_value += _type_count_white[TWO] * 10;
		black_value += _type_count_black[TWO] * 10;

		// 眠而加分
		white_value += _type_count_white[STWO] * 4;
		black_value += _type_count_black[STWO] * 4;
	}
	else // 该黑棋走 分析同上
	{
		if (_type_count_black[FOUR] > 0)
			return 9990;
		if (_type_count_black[SFOUR] > 0)
			return 9980;
	
		if (_type_count_white[FOUR] > 0)
			return -9970;

		if (_type_count_white[SFOUR] > 0 && _type_count_black[THREE] > 0)
			return -9960;

		if (_type_count_black[THREE] > 0 && _type_count_black[SFOUR] > 0)
			return 9950;

		if (_type_count_white[THREE] > 1
			&& _type_count_black[THREE] == 0
			&& _type_count_black[STHREE] == 0)
			return -9940;

		if (_type_count_black[THREE] > 1)
			black_value += 2000;
		else if (_type_count_black[THREE] == 1)
			black_value += 200;

		if (_type_count_white[THREE] > 1)
			black_value += 500;
		else if (_type_count_white[THREE] == 1)
			black_value += 100;

		black_value += _type_count_black[STHREE] * 20;
		white_value += _type_count_white[STHREE] * 20;
		
		black_value += _type_count_black[TWO] * 10;
		white_value += _type_count_white[TWO] * 10;
		
		black_value += _type_count_black[STWO] * 4;
		white_value += _type_count_white[STWO] * 4;
		
	}

	// 加上位置分数
	for (int i = 0; i < _cbsize; i++)
		for (int j = 0; j < _cbsize; j++)
		{
		ChessType type = chessboard.GetChess(i, j);
		if (type == CT_WHITE)
			white_value += _posvalue[i][j];
		else if (type == CT_BLACK)
			black_value += _posvalue[i][j];
		}

	if (isWhiteTurn)
		return white_value - black_value;
	else
		return black_value - white_value;
}

int Evaluator::analysisHorizon(const ChessBoard& chessboard, int i, int j)
{
    ChessType tmpline[CB_MAXSIZE];
    for(int k=0; k<_cbsize; k++)
        tmpline[k] = chessboard.GetChess(i, k);
    analysisLine(tmpline, _cbsize, j);
    for(int k=0; k<_cbsize; k++)
    {
        if(_tmp_record[k] != TOANALYSIS)
            _type_record[i][k][HORIZON] = _tmp_record[k];
    }
    return _type_record[i][j][HORIZON];
}

int Evaluator::analysisVertical(const ChessBoard& chessboard, int i, int j)
{
    ChessType tmpline[CB_MAXSIZE];
    for(int k=0; k<_cbsize; k++)
        tmpline[k] = chessboard.GetChess(k, j);
	analysisLine(tmpline, _cbsize, i);
    for(int k=0; k<_cbsize; k++)
    {
        if(_tmp_record[k] != TOANALYSIS)
            _type_record[k][j][VERTICAL] = _tmp_record[k];
    }
    return _type_record[i][j][VERTICAL];
}

int Evaluator::analysisLeftUp(const ChessBoard& chessboard, int i, int j)
{
	ChessType tmpline[CB_MAXSIZE];
	int istart, jstart;
	if (i < j)
	{
		istart = 0;
		jstart = j - i;
	}
	else
	{
		istart = i - j;
		jstart = 0;
	}
	int k;
	for (k = 0; i < _cbsize; k++)
	{
		if (istart + k >= _cbsize || jstart + k >= _cbsize)
			break;
		tmpline[k] = chessboard.GetChess(istart+k, jstart+k);
	}
	analysisLine(tmpline, k, j - jstart);
	for (int t = 0; t < k; ++t)
	{
		if (_tmp_record[t] != TOANALYSIS)
			_type_record[istart + t][jstart + t][LEFTUP] = _tmp_record[t];
	}

	return _type_record[i][j][LEFTUP];
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
    for(int t=0; t<k; t++)
    {
        if(_tmp_record[t] != TOANALYSIS)
            _type_record[istart-t][jstart+t][LEFTDOWN] = _tmp_record[t];
    }
    return _type_record[i][j][LEFTDOWN];
}

int Evaluator::analysisLine(ChessType line[], int size, int pos)
{
	memset(_tmp_record, TOANALYSIS, sizeof(_tmp_record));
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
		for (int k = leftValid; k <= rightValid; k++)
			_tmp_record[k] = ANALYSISED;
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
		bool leftThree = false;
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
					else if (line[leftSame - 3] == CT_NULL) // +0+00
					{
						_tmp_record[leftSame - 2] = ANALYSISED;
						_tmp_record[leftSame] = STHREE;
					}
					else
						leftThree = true;
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
                        _tmp_record[rightSame+2] = ANALYSISED;
                        _tmp_record[rightSame] = STHREE;
                    }
                }
            }
            else
            {
				if (leftThree)
					_tmp_record[rightSame] = STHREE;
                else if(leftClear)
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

#include<iostream>
using std::cout;
using std::endl;
void Evaluator::PrintTypeRecord()
{
	cout << "Herizon" << endl;
	for (int i = 0; i < _cbsize; i++)
	{
		for (int j = 0; j < _cbsize; j++)
			cout << (int)(_type_record[i][j][HORIZON]) << " ";
		cout << endl;
	}

	cout << "Vertical" << endl;
	for (int i = 0; i < _cbsize; i++)
	{
		for (int j = 0; j < _cbsize; j++)
			cout << (int)(_type_record[i][j][VERTICAL]) << " ";
		cout << endl;
	}

	cout << "LeftDown" << endl;
	for (int i = 0; i < _cbsize; i++)
	{
		for (int j = 0; j < _cbsize; j++)
			cout << (int)(_type_record[i][j][LEFTDOWN]) << " ";
		cout << endl;
	}

	cout << "LeftUp" << endl;
	for (int i = 0; i < _cbsize; i++)
	{
		for (int j = 0; j < _cbsize; j++)
			cout << (int)(_type_record[i][j][LEFTUP]) << " ";
		cout << endl;
	}
}
