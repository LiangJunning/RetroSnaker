#pragma once

using namespace std;

typedef struct COOR_t 
{
	int x;
	int y;
}COOR;

typedef struct SPU_t 
{//Snake Position Unit
	COOR cp;//Current Position
	SPU_t *next;
}SPU;

typedef struct SNAKE_t 
{
	int lengh;
	SPU pos;
}SNAKE;

typedef struct GSettings_t
{//Game Settings
	int a;
	int b;
	int feq;//Frequency     Unit:feq t/s
	char border;
	char snakeu;//Snake Unit
	int init_snake_len;//Initial Snake Lengh
}GSettings;

typedef struct CuState_t
{
	int time;//Unit:s
	int score;
	int dir;//Direction
}CuState;

enum eDirection
{
	UP,DOWN,LEFT,RIGHT
};

//���
void play(GSettings Settings);

//ǰ��
void Forward();

//��ת
void TurnLeft();

//��ת
void TurnRight();

//����
void TrunDown();

//����
void TurnUp();

//���
static void output(char * map, GSettings Settings, CuState State);

//��ʼ��map
void init_map(char** map, int a, int b, GSettings Settings);

//��תmap
inline char* goto_map(int x, int y, char* map, int b);

static inline void putnchr(char chr, int n);
