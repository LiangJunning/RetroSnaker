#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
#include <conio.h>
#include "core.h"

void gotoxy(HANDLE hOut, int x, int y);
void getxy(HANDLE hOut, int &x, int &y);
/*int main()
{
	int x, y;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hOut, 5, 5);
	printf("position: 5, 5");
	getxy(hOut, x, y);
	getch();
	gotoxy(hOut, x, y - 1);
	getch();
	CloseHandle(hOut);
}*/
void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
void getxy(HANDLE hOut, int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hOut, &screen_buffer_info);
	x = screen_buffer_info.dwCursorPosition.X;
	y = screen_buffer_info.dwCursorPosition.Y;
}