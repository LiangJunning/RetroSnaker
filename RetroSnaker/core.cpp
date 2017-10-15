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

	init_map(map, Settings.a, Settings.b);
}

void output(char * map)
{
}

void init_map(char * map, int a, int b)
{
	map = (char*)malloc((b + 1)*a + sizeof(char));
}

inline char * goto_map(char * map, int x, int y)
{
	return nullptr;
}
