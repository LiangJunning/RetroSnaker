#include "stdafx.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#define SchemesNum 4

extern void gotoxy(HANDLE hOut, int x, int y);
extern void getxy(HANDLE hOut, int &x, int &y);

//Private
int inline static IsEatSelf(CuState *State);
static inline void putnchr(char chr, int n);
static void wait(int mm);

const char *strlist[] = 
{ 
	"Retro Snaker     Score:",//0.title prefix
	"Press 'w''s''a''d' to go up, down, left, right. Press 'space' to pause.",//1.runtime tips
	"Press 'w''s''a''d' to continue and go up, down, left, right.           ",//2.pause tips
	"Bump!                                                                  ",//3.bump
	"Eat self!                                                              ",//4.eat self
	"Game Over! You are Winner!                                             ",//5.game over
	"Welcome!\n",//6.Welcome
	"Here's the default scheme:",//7.Start tips
	"Press enter to start game. Press any other key to select other game schemes.",//8.Start tips
	"Please enter a number to select schemes:",//9.select scheme
	"Error:Input invalid! Please try again."//10.Input invalid
};

const GSettings schemes[] = {
	{ 10,30,4,'=','O','$',' ',5 },
	{ 15,45,6,'=','O','$',' ',5 },
	{ 20,60,8,'=','O','$',' ',5 },
	{ 30,90,16,'=','O','$',' ',5 }
};

void play(GSettings Settings)
{
	SNAKE sn = { 0 };
	CuState State;
	char cmd[MAX_PATH];
	
	StartScreen(&Settings);
	init_snake(&State, Settings);
	sprintf(cmd, "title %s%d", strlist[0], State.score);
	system(cmd);
	output(Settings, State);
	put_food(Settings, &State);
	{//trigger
		char ch = _getch();
		while (ch != 'd' && ch != 's')
			ch = _getch();
		State.dir = ch == 's' ? DOWN : RIGHT;
	}
	Forward(Settings, &State);
	free_snake(&State.snake);
	getchar();
}

void init_snake(CuState *State, GSettings Settings)
{
	SPU *cu,*head;

	srand((unsigned int)time(0));
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
	int len = State.snake.length, fork = 0;
	char bo = Settings.border;
	int x, y;
	char cmd[MAX_PATH];
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	sprintf(cmd, "mode con cols=%d lines=%d", Settings.b + 2, Settings.a + 4 + (int)(strlen(strlist[1]) / (Settings.b + 2)));
	system(cmd);
	putnchr(bo, Settings.b + 2);
	putchar('\n');
	for (int i = 0; i < Settings.a; i++,fork=0)
	{
		putchar(bo);
		if (i == 0)
		{
			putnchr(Settings.snakeu, len);
			putnchr(Settings.fill, Settings.b - len);
		}
		else
			putnchr(Settings.fill, Settings.b);
		putchar(bo);
		putchar('\n');
	}
	putnchr(bo, Settings.b + 2);
	putchar('\n');
	getxy(hOut, x, y);
	puts(strlist[1]);
	gotoxy(hOut, x, y);
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

void bump(int type)
{
	if (type == 0)
		puts(strlist[3]);
	else if (type == 1)
		puts(strlist[4]);
	else if (type == 2)
		puts(strlist[5]);
}

void put_food(GSettings Settings, CuState * State)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SPU *cur = State->snake.head;
	int x, y;
	int slen = State->snake.length;
	int i, IsInvalid = 0;

	getxy(hOut, x, y);
	State->food = { rand() % Settings.b ,rand() % Settings.a };
	for (i = 0; i < slen - 1; i++)
	{
		if (cur->pos.x==State->food.x&&cur->pos.y==State->food.y)
		{
			put_food(Settings, State);
			IsInvalid = 1;
			break;
		}
		cur = cur->next;
	}
	if (!IsInvalid)
	{
		gotoxy(hOut, State->food.x + 1, State->food.y + 1);
		putchar(Settings.food);
		gotoxy(hOut, x, y);
	}
}

int got_food(GSettings Settings, CuState * State)
{
	char cmd[MAX_PATH];
	int x, y;
	SPU *nexth = (SPU*)malloc(sizeof(SPU));
	SNAKE *sn = &State->snake;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	sprintf(cmd, "title %s%d", strlist[0], ++State->score);
	system(cmd);
	*nexth = { State->food,sn->head,sn->head->last };
	sn->head->last->next = nexth;
	sn->head->last = nexth;
	sn->head = nexth;
	sn->length++;
	getxy(hOut, x, y);
	gotoxy(hOut, State->food.x + 1, State->food.y + 1);
	putchar(Settings.snakeu);
	gotoxy(hOut, x, y);
	if (sn->length == Settings.a*Settings.b)
		return 1;
	put_food(Settings, State);
	return 0;
}

void StartScreen(GSettings * Settings)
{
	char ch;
	int isinvalid = 1;
	puts(strlist[6]);
	puts(strlist[7]);
	printf("Column: %d\nLine: %d\nInitial Speed: %d times/sec\n", Settings->b, Settings->a, Settings->feq);
	puts(strlist[8]);
	if (_getch() == '\r')
	{
		system("cls");
		return;
	}
	system("cls");
	for (int i = 0; i < SchemesNum; i++)
		printf("%d.\nColumn: %d\nLine: %d\nInitial Speed: %d times/sec\n\n", i + 1, schemes[i].b, schemes[i].a, schemes[i].feq);
	printf("%s_\b", strlist[9]);
	while (1)
	{
		ch = _getch();
		putchar(ch);
		if (isdigit(ch) && ch - '0' > 0 && ch - '0' <= SchemesNum)
		{
			*Settings = schemes[ch - '0' - 1];
			return;
		}
		system("cls");
		puts(strlist[10]);
		for (int i = 0; i < SchemesNum; i++)
			printf("%d.\nColumn: %d\nLine: %d\nInitial Speed: %d times/sec\n\n", i + 1, schemes[i].b, schemes[i].a, schemes[i].feq);
		printf("%s_\b", strlist[9]);
	}
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
			if (state->dir != RIGHT)
				state->dir = LEFT;
			break;
		case 's':
			if (state->dir != UP)
				state->dir = DOWN;
			break;
		case 'd':
			if (state->dir != LEFT)
				state->dir = RIGHT;
			break;
		case ' ':
			state->dir = PAUSE;
			break;
		default:
			break;
		}
	}
		
	return 0;
}

void Forward(GSettings Settings, CuState * State)
{
	HANDLE hKeypro;
	int isbump = 0, ispause = 0;
	SNAKE *sn = &State->snake;
	COOR newpos;

	State->interval = (int)((1.0f / (float)Settings.feq)*1000.0f);
	hKeypro = CreateThread(NULL, 2, keypro, State, 0, nullptr);
	while (1)
	{
		if (ispause&&State->dir != PAUSE)
		{
			int x, y;
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			getxy(hOut, x, y);
			puts(strlist[1]);
			gotoxy(hOut, x, y);
			ispause = 0;
		}
		switch (State->dir)
		{
			case DOWN:
			{
				newpos = { sn->head->pos.x,sn->head->pos.y + 1 };
				if (newpos.y == Settings.a)
				{
					isbump = 1;
					break;
				}
			}
			break;
			case UP:
			{
				newpos = { sn->head->pos.x,sn->head->pos.y - 1 };
				if (newpos.y == -1)
				{
					isbump = 1;
					break;
				}
			}
			break;
			case LEFT:
			{
				newpos = { sn->head->pos.x-1,sn->head->pos.y};
				if (newpos.x == -1)
				{
					isbump = 1;
					break;
				}
			}
			break;
			case RIGHT:
			{
				newpos = { sn->head->pos.x+1,sn->head->pos.y};
				if (newpos.x == Settings.b)
				{
					isbump = 1;
					break;
				}
			}
			break;
			case PAUSE:
			{
				if (!ispause)
				{
					int x, y;
					HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
					getxy(hOut, x, y);
					puts(strlist[2]);
					gotoxy(hOut, x, y);
				}
				ispause = 1;
				continue;
			}
		}
		if (newpos.x == State->food.x&&newpos.y == State->food.y)
		{
			if (got_food(Settings, State))
			{
				bump(2);
				break;
			}
		}
		else
			refresh(Settings, State, newpos);
		if (IsEatSelf(State))
			break;
		if (isbump)
		{
			TerminateThread(hKeypro, 0);
			bump(0);
			break;
		}
		wait(State->interval);
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

inline int IsEatSelf(CuState * State)
{
	SNAKE *sn = &State->snake;
	SPU *cur=sn->head->next;
	int slen = sn->length;
	int i;
	
	for (i = 0; i < slen - 1; i++)
	{
		if (sn->head->pos.x == cur->pos.x&&sn->head->pos.y == cur->pos.y)
		{
			bump(1);
			return 1;
		}
		cur = cur->next;
	}

	return 0;
}