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
	int dir;
	int ldir;//lase dir
	SNAKE snake;
}CuState;

enum eDirection
{
	UP,DOWN,LEFT,RIGHT
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

//װ��
void bump(CuState State);

//static DWORD __stdcall keypro(LPVOID lpParam);

static inline void putnchr(char chr, int n);

static void wait(int mm);