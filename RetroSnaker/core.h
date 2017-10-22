#pragma once

using namespace std;

typedef struct COOR_t 
{
	int x;
	int y;
}COOR;

typedef struct SPU_t 
{//Snake Position Unit
	COOR pos;//Position
	SPU_t *next;
	SPU_t *last;
}SPU;

typedef struct SNAKE_t 
{
	int length;
	SPU *head;
}SNAKE;

typedef struct GSettings_t
{//Game Settings
	int a;
	int b;
	int feq;//Frequency     Unit:feq t/s
	char border;
	char snakeu;//Snake Unit
	char fill;
	int init_snake_len;//Initial Snake length
}GSettings;

typedef struct CuState_t
{
	int time;//Unit:s
	int score;
	int dir;//Direction 作为消息
	SNAKE snake;
}CuState;

enum eDirection //作为消息
{
	FORWARD,UP,DOWN,LEFT,RIGHT
};

//入口
void play(GSettings Settings);

//前进
void Forward();

//左转
void TurnLeft();

//右转
void TurnRight();

//向下
void TrunDown();

//向上
void TurnUp();

/*//输出
void output(char * map, GSettings Settings, CuState State);

//刷新
void refresh(char** map, GSettings Settings, CuState State);

//初始化map
void init_map(char** map, int a, int b, GSettings Settings);

//跳转map
inline char* goto_map(int x, int y, char* map, int b);*///dm

//初始化snake
void init_snake(CuState *State, GSettings Settings);

//释放snake
void free_snake(SNAKE* Snake);

//输出
void output(GSettings Settings, CuState State);

static inline void putnchr(char chr, int n);
