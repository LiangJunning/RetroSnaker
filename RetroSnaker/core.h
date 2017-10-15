#pragma once

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

struct GSettings 
{//Current Settings
	int a;
	int b;
	int feq;//Frequency     Unit:feq t/s
	char border;
	char snakeu;//Snake Unit
};

struct CuState
{
	int time;//Unit:s
	int score;
	int dir;//Direction
};

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
static void output(char* map);

//��ʼ��map
void init_map(char* map, int a, int b);

//��תmap
inline char* goto_map(char* map, int x, int y);
