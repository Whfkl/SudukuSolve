#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
int a[9][9] =
{
	8,0,0,  0,0,0,  0,0,0,
	0,0,3,  6,0,0,  0,0,0,
	0,7,0,  0,9,0,  2,0,0,

	0,5,0,  0,0,7,  0,0,0,
	0,0,0,  0,4,5,  7,0,0,
	0,0,0,  1,0,0,  0,3,0,

	0,0,1,  0,0,0,  0,6,8,
	0,0,8,  5,0,0,  0,1,0,
	0,9,0,  0,0,0,  4,0,0

};
void goto_xy(int x, int y)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x*2,y*2 };
	SetConsoleCursorPosition(hOut, pos);
	Sleep(0);
	printf("%d ", a[y][x]);
}
void outputIt()
{
	printf("\n\n");
	int i, j, i1, j1;
	i1 = 0; j1 = 0;
	for (i = 0; i < 9; i++)
	{
		j1++;
		for (j = 0; j < 9; j++)
		{
			i1++;
			printf("%d ", a[i][j]);
			if (i1 % 3 == 0)
				printf("  ");
		}
		if (j1 % 3 == 0)
			printf("\n");
		printf("\n");
	}
}
int check(int x, int y, int p)
{
	int i, j, k;
	int index0 = 0;	int index1 = 0;	int index2 = 0;

	for (i = 0; i < 9; i++)
	{
		if (p == a[i][x])
			index0++;
		if (p == a[y][i])
			index1++;
	}
	for (j = (x / 3)*3; j < ((x / 3)*3 + 3); j++)
		for (k = (y / 3)*3; k < ((y / 3)*3 + 3); k++)
		{
			if (a[k][j] == p){ 
				index2++;
				} 
		}
	if (index0 == 0 && index1 == 0 && index2 == 0) 
	{
		return 1;
	}
	else
		return 0;
}
int nextPos(int y, int x)
{
	int nx, ny, num;
	if (x != 8)
	{
		nx = x + 1;
		ny = y;
	}
	else
	{
		nx = 0;
		ny = y + 1;
	}
	num = nx * 10 + ny;
	return num;
}

int run(int x, int y)
{
	if (x == 0 && y == 9)
		return 1;
	int nx, ny, num;
	num = nextPos(y, x);
	nx = num / 10; ny = num % 10;
	if (a[y][x] != 0)
	{
		goto_xy(x,y);
		run(nx, ny);
	}

	else
	{
		int p;
 		for (p = 1; p <= 9; p++)
		{
			if (check(x, y, p))
			{
				a[y][x] = p;
				goto_xy(x,y);

				if (run(nx, ny))
					return 1;
				else
				{
					a[y][x] = 0;
					goto_xy(x,y);
				}
			}
		}
		return 0;
	}
}
int main()
{
	run(0, 0);
	int i, j;
	outputIt();
	return 0;
}
