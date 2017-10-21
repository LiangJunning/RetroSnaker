// RetroSnaker.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "core.h"
#include <stdlib.h>
#include <windows.h>
#include <iostream>
//#include <wchar.h>

using namespace std;

void roll_test(void);

extern void gotoxy(HANDLE hOut, int x, int y);
extern void getxy(HANDLE hOut, int &x, int &y);

int main()
{
	/*while (1)
	{
		static int i;
		printf("%d\n", i++);
		printf("%d\n", i + 1);
		printf("%d\n", i + 2);
		printf("%d\n", i + 3);
		printf("%d\n", i + 4);
		printf("%d\n", i + 5);

		//fflush(stdout);
		//Sleep(5);
		system("cls");
	}*/
	/*HANDLE hWnd= GetStdHandle(STD_OUTPUT_HANDLE);
	printf("a\nb\ncdefgg\n\n\n");
	gotoxy(hWnd,2,2);
	putchar('x');
	getchar();
	CloseHandle(hWnd);*/

	GSettings Settings =
	{
		20,
		30,
		1,
		'=',
		'0',
		5
	};
	play(Settings);
    return 0;
}

void roll_test(void)
{
	
}
