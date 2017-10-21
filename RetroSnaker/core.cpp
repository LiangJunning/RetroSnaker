#include "stdafx.h"
#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

extern void gotoxy(HANDLE hOut, int x, int y);
extern void getxy(HANDLE hOut, int &x, int &y);

void play(GSettings Settings)
{
	SNAKE sn = { 0 };
	CuState State;
	
	init_snake(&State, Settings);

	//char* map;//dm
	//init_map(&map, Settings.a, Settings.b,Settings);//dm
	getchar();
	free_snake(&State.snake);
}

/*void output(char * map, GSettings Settings,CuState State)
{
	putnchr(Settings.border, Settings.b + 2);
	putchar('\n');
	
	
}

void refresh(char ** map, GSettings Settings, CuState State)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

}

void init_map(char ** map, int a, int b, GSettings Settings)
{
	*map = (char*)malloc((b + 1)*a + sizeof(char));
	memset(*map, 32, (b + 1)*a + sizeof(char));
	//const char * (gm) = (goto_map)(char* map, int x, int y, int b = b);
	//char * (*gm)(int x, int y, char* map, int b) = goto_map;
	*goto_map(0, 0, *map, b);
	for (int i = 0; i < Settings.init_snake_len; i++)
		*goto_map(i, 0, *map, b) = Settings.snakeu;

}

inline char* goto_map(int x, int y, char* map, int b)
{
	return (map + (y + 1)*(b + 1) + x);
}*///dm

void init_snake(CuState *State, GSettings Settings)
{
	SPU *cu,*head;

	*State = { 0 };
	State->snake.lengh = Settings.init_snake_len;
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
	for (int i = 1; i < Snake->lengh; i++, cu = cu->next)
		free(cu->last);
}

inline void putnchr(char chr, int n)
{
	for (int i; i < n; i++)
		putchar(chr);
}
