#include "stdafx.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

void play(GSettings Settings)
{
	SNAKE sn = { 0 };
	CuState State;
	char* map;

	init_map(&map, Settings.a, Settings.b,Settings);
}

void output(char * map, GSettings Settings,CuState State)
{

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
}

inline void putnchr(char chr, int n)
{
	for (int i; i < n; i++)
		putchar(chr);
}
