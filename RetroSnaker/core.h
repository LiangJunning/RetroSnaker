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
	int dir;//Direction ��Ϊ��Ϣ
	SNAKE snake;
}CuState;

enum eDirection //��Ϊ��Ϣ
{
	FORWARD,UP,DOWN,LEFT,RIGHT
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

/*//���
void output(char * map, GSettings Settings, CuState State);

//ˢ��
void refresh(char** map, GSettings Settings, CuState State);

//��ʼ��map
void init_map(char** map, int a, int b, GSettings Settings);

//��תmap
inline char* goto_map(int x, int y, char* map, int b);*///dm

//��ʼ��snake
void init_snake(CuState *State, GSettings Settings);

//�ͷ�snake
void free_snake(SNAKE* Snake);

//���
void output(GSettings Settings, CuState State);

static inline void putnchr(char chr, int n);
