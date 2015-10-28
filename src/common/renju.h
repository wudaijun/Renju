/*****************************************************************************
* @author 	: wudaijun
* @date 	: 2015/10/21 21:01
* @email	: wdjlost@gmail.com
* @doc		: 定义一些全局共享的宏和配置
*****************************************************************************/
#pragma  once

// 棋子类型定义 Chess Type
#define CT_NULL  0
#define CT_WHITE 1
#define CT_BLACK 2

// 默认棋盘大小
#define CB_SIZE 11

// 最大棋盘大小
#define CB_MAXSIZE 30

// 搜索深度
#define MAX_DEPTH 5
#define DEFAULT_DEPTH 2

typedef char ChessType;

// 游戏结果
enum GameResult
{
	FIGHTING = 0,	// 未分出胜负
	BLACK_WIN,		// 黑棋胜出
	WHITE_WIN,		// 白棋胜出
	DRAW			// 平局(棋子放满)
};

// 统计数据
struct StatInfo
{
	unsigned int cost_ms;	// 花费的时间(毫秒)
	int eval_cnt;			// 调用估值核心的次数
};


