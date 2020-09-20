#include <stdio.h>
#include <Windows.h>
#include "Render.h"

HANDLE Handle;

enum Color {
	COLOR_BLACK = 0, COLOR_DARKBLUE, COLOR_DARKGREEN, COLOR_DARKSKY, COLOR_DARKRED, COLOR_DARKPINK, COLOR_DARKYELLOW, COLOR_DARKWHITE,
	COLOR_GRAY, COLOR_BLUE, COLOR_GREEN, COLOR_SKY, COLOR_RED, COLOR_PINK, COLOR_YELLOW, COLOR_WHITE
};

// ȭ�� ��� �Լ�
void Render()
{
	InitializeRender();
	SetPixelColor(2, 2, COLOR_BLACK, COLOR_WHITE);
	printf("������ �Ǿ����ϴ�.");
}

void InitializeRender()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

// x�� y ��ǥ�� Ŀ�� �ű�� �Լ�
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