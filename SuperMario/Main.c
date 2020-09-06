#include <stdio.h>
#include <Windows.h>

// 자료형 bool을 사용할 수 있도록 선언 및 정의
typedef enum bool{ false = 0, true } bool;

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x << 1;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main()
{

}