#include "stdafx.h"
#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

extern void gotoxy(HANDLE hOut, int x, int y);
extern void getxy(HANDLE hOut, int &x, int &y);

void play(GSettings Settings)
{
	SNAKE sn = { 0 };
	CuState State;
	
	init_snake(&State, Settings);
	output(Settings, State);
	{//trigger
		char ch = _getch();
		while (ch != 'd' && ch != 's')
			ch = _getch();
		State.dir = ch == 's' ? DOWN : RIGHT;
	}
	Forward(Settings, &State);
	//char* map;//dm
	//init_map(&map, Settings.a, Settings.b,Settings);//dm
	getchar();
	free_snake(&State.snake);
}

void init_snake(CuState *State, GSettings Settings)
{
	SPU *cu,*head;

	*State = { 0 };
	State->snake.length = Settings.init_snake_len;
	cu = head = State->snake.head = (SPU*)malloc(sizeof(SPU));
	head->pos = { Settings.init_snake_len - 1,0 };
	for (int i = Settings.init_snake_len - 2; i >= 0; i--)
	{
		cu->next = (SPU*)malloc(sizeof(SPU));
		memset(cu->next, 0, sizeof(SPU));
		cu->next->last = cu;
		cu = cu->next;//Enter Next Level
		cu->pos = { i,0 };
	}
	cu->next = head;//Make A Ring
	head->last = cu;
}

void free_snake(SNAKE * Snake)
{
	SPU *cu=Snake->head;
	for (int i = 1; i < Snake->length; i++, cu = cu->next)
		free(cu->last);
}

void output(GSettings Settings, CuState State)
{
	int len = State.snake.length;
	int fork = 0;
	char bo = Settings.border;
	COOR *coors = (COOR*)malloc(sizeof(COOR)*State.snake.length);
	SPU *cu=State.snake.head;


	memset(coors, 0, sizeof(COOR)*len);
	for (int i = 0; i < len; i++)
	{
		*(coors + i) = cu->pos;
		cu = cu->next;
	}
	{//sort
		int temp;
		for (int i = 0; i<len - 1; i++)
			for (int j = i + 1; j<len; j++) /*注意循环的上下限*/
				if ((coors+i)->x>(coors + j)->x) 
				{
					temp = (coors+i)->x;
					(coors+i)->x = (coors+j)->x;
					(coors+j)->x = temp;
				}
	}
	putnchr(bo, Settings.b + 2);
	putchar('\n');

	for (int i = 0; i < Settings.a; i++)
	{
	putchar(bo);
	for (int j = 0; j < Settings.b; j++)
	{
		if ((coors + fork)->y == i)
		{
			putchar(Settings.snakeu);
			fork++;
		}
		else
			putchar(Settings.fill);
	}
	putchar(bo);
	putchar('\n');
	}

	putnchr(bo, Settings.b + 2);
	putchar('\n');
}

void refresh(GSettings Settings, CuState * State, COOR newpos)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SNAKE *sn=&State->snake;
	int x, y;
	
	getxy(hOut,x, y);
	gotoxy(hOut, sn->head->last->pos.x + 1, sn->head->last->pos.y + 1);
	putchar(Settings.fill);
	gotoxy(hOut, newpos.x + 1, newpos.y + 1);
	putchar(Settings.snakeu);
	gotoxy(hOut, x, y);
	sn->head->last->pos = newpos;
	sn->head = sn->head->last;
}

void bump(CuState State)
{
	puts("Bump!");
}

DWORD __stdcall keypro(LPVOID lpParam)
{
	CuState *state=(CuState*)lpParam;
	while (1)
	{
		switch (_getch())
		{
		case 'w':
			if (state->dir != DOWN)
				state->dir = UP;
			break;
		case 'a':
			//state->ldir = state->dir;
			if (state->dir != RIGHT)
				state->dir = LEFT;
			break;
		case 's':
			//state->ldir = state->dir;
			if (state->dir != UP)
				state->dir = DOWN;
			break;
		case 'd':
			//state->ldir = state->dir;
			if (state->dir != LEFT)
				state->dir = RIGHT;
			break;
			/*case default:
			break;*/
		}
	}
		
	return 0;
}

void Forward(GSettings Settings, CuState * State)
{
	HANDLE hKeypro;
	int interval = (int)((1.0f / (float)Settings.feq)*1000.0f);
	int isbump = 0;
	SNAKE *sn = &State->snake;
	COOR newpos;
	State->ldir = State->dir;

	hKeypro = CreateThread(NULL, 2, keypro, State, 0, nullptr);
	/*while (1)
		printf("%d\n", State->dir);*/
	while (1)
	{
		switch (State->dir)
		{
			case DOWN:
			{
				newpos = { sn->head->pos.x,sn->head->pos.y + 1 };
				refresh(Settings, State, newpos);
				if (sn->head->pos.y == Settings.a)
				{
					isbump = 1;
					break;
				}
			}
			break;
			case UP:
			{
				newpos = { sn->head->pos.x,sn->head->pos.y - 1 };
				refresh(Settings, State, newpos);
				if (sn->head->pos.y == -1)
				{
					isbump = 1;
					break;
				}
			}
			break;
			case LEFT:
			{
				newpos = { sn->head->pos.x-1,sn->head->pos.y};
				refresh(Settings, State, newpos);
				if (sn->head->pos.x == -1)
				{
					isbump = 1;
					break;
				}
			}
			break;
			case RIGHT:
			{
				newpos = { sn->head->pos.x+1,sn->head->pos.y};
				refresh(Settings, State, newpos);
				if (sn->head->pos.x + 1 == Settings.b + 1)
				{
					isbump = 1;
					break;
				}
			}
			break;
		}
		if (isbump)
		{
			TerminateThread(hKeypro, 0);
			bump(*State);
			break;
		}
		wait(interval);
	}
}


inline void putnchr(char chr, int n)
{
	for (int i = 0; i < n; i++)
		putchar(chr);
}

void wait(int mm)
{
	clock_t s = clock();
	while (((int)((float)(clock() - s) / (float)CLOCKS_PER_SEC * 1000.0f)) < mm)
		continue;
}
