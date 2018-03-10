#pragma once

using namespace std;

/*
Coordinate System
bbbbbbbbbbbb->x
boq        b
bp         ba=3
b         rb
bbbbbbbbbbbb
|   b=10
y
Examples:o(0,0) p(0,1) q(1,0) r(b-1,a-1)
*/

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
	int a;//y
	int b;//x
	int feq;//Frequency     Unit:feq t/s
	char border;
	char snakeu;//Snake Unit
	char food;
	char fill;
	int init_snake_len;//Initial Snake length
}GSettings;

typedef struct CuState_t
{
	int time;//Unit:s
	int score;
	int dir;
	int interval;
	int ldir;//last dir
	COOR food;
	SNAKE snake;
}CuState;

enum eDirection
{
	UP,DOWN,LEFT,RIGHT,PAUSE
};

//���
void play(GSettings Settings);

//ǰ��
void Forward(GSettings Settings, CuState * State);

//��ʼ��snake
void init_snake(CuState *State, GSettings Settings);

//�ͷ�snake
void free_snake(SNAKE* Snake);

//���
void output(GSettings Settings, CuState State);

//ˢ��
void refresh(GSettings Settings, CuState *State, COOR newpos);

//��Ϸ������ʾ
void bump(int type);

//����ʳ��
void put_food(GSettings Settings, CuState *State);

//�õ�ʳ��
int got_food(GSettings Settings, CuState *State);

//��ʾ��ʼ��Ļ
void StartScreen(GSettings* Settings);

//static DWORD __stdcall keypro(LPVOID lpParam);
