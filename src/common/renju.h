/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 21:01
* @email	: wdjlost@gmail.com
* @doc		: ����һЩȫ�ֹ���ĺ������
*****************************************************************************/
#pragma  once

// �������Ͷ��� Chess Type
#define CT_NULL  0
#define CT_WHITE 1
#define CT_BLACK 2

// Ĭ�����̴�С
#define CB_SIZE 11

// ������̴�С
#define CB_MAXSIZE 30

// �������
#define MAX_DEPTH 5
#define DEFAULT_DEPTH 2

typedef char ChessType;

// ��Ϸ���
enum GameResult
{
	FIGHTING = 0,	// δ�ֳ�ʤ��
	BLACK_WIN,		// ����ʤ��
	WHITE_WIN,		// ����ʤ��
	DRAW			// ƽ��(���ӷ���)
};

// ͳ������
struct StatInfo
{
	unsigned int cost_ms;	// ���ѵ�ʱ��(����)
	int eval_cnt;			// ���ù�ֵ���ĵĴ���
};


