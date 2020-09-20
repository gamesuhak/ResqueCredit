#include <stdio.h>
#include <Windows.h>
#include "Render.h"

HANDLE Handle;

enum Color {
	COLOR_BLACK = 0, COLOR_DARKBLUE, COLOR_DARKGREEN, COLOR_DARKSKY, COLOR_DARKRED, COLOR_DARKPINK, COLOR_DARKYELLOW, COLOR_DARKWHITE,
	COLOR_GRAY, COLOR_BLUE, COLOR_GREEN, COLOR_SKY, COLOR_RED, COLOR_PINK, COLOR_YELLOW, COLOR_WHITE
};

// 화면 출력 함수
void Render()
{
	InitializeRender();
	SetPixelColor(2, 2, COLOR_BLACK, COLOR_WHITE);
	printf("렌더링 되었습니다.");
}

void InitializeRender()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

// x와 y 좌표로 커서 옮기는 함수
void SetPoint(int x, int y)
{
	COORD Pos;
	Pos.X = x << 1;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetPixelColor(int x, int y, Color textColor, Color backColor)
{
	printf("textColor = %d, backColor = %d\n", textColor, (backColor << 4));
	printf("textColor = %d, backColor = %d", textColor, (backColor * 16));

	SetPoint(x, y);
	SetConsoleTextAttribute(Handle, textColor + (backColor << 4));
	printf("  ");
}