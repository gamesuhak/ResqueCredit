#include "Screen.h"

#include <stdio.h>

// ȭ�� ������ ������ �ִ� �ڵ��� ������ ����
HANDLE Handle;

void InitializeScreen()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTitle("Title");
	//system("cls");
	SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	RemoveScrollbar();
	ViewCursor(0);
}

// Ŀ�� �����
void ViewCursor(char value)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = value;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(Handle, &ConsoleCursor);
} // ���� : https://blog.naver.com/upssuyo/80092210109

void RemoveScrollbar()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(Handle, &info);
	COORD newSize =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(Handle, newSize);
}

void SetScreenSize(int width, int height)
{
	char command[COMMAND_MAX] = "mode con:cols=";
	char buffer[BUFFER_MAX] = "";

	sprintf(buffer, "%d", width + 1);
	strcat(command, buffer);
	strcat(command, " lines=");
	sprintf(buffer, "%d", height);
	strcat(command, buffer);

	system(command);
	//system("mode con:cols=176 lines=64");
}

// x�� y ��ǥ�� Ŀ�� �ű�� �Լ�
void SetPoint(int x, int y)
{
	COORD Pos;
	Pos.X = x << 1;
	Pos.Y = y;
	SetConsoleCursorPosition(Handle, Pos);
}

void SetPixelColor(int x, int y, Color textColor, Color backColor)
{
	if (backColor < 0)
	{
		return;
	}
	SetPoint(x, y);
	SetConsoleTextAttribute(Handle, textColor + (backColor << 4)); // backColor << 4�� backColor * 16�� ����
	printf("  ");
}

