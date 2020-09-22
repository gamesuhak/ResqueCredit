#include "Screen.h"
#define SCREEN_WIDTH 176
#define SCREEN_HEIGHT 128

// 화면 정보를 가지고 있는 핸들을 저장할 변수
HANDLE Handle;

void InitializeScreen()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Title");
	system("cls");
	SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	RemoveScrollbar();
}

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

// x와 y 좌표로 커서 옮기는 함수
void SetPoint(int x, int y)
{
	COORD Pos;
	Pos.X = x << 1;
	Pos.Y = y;
	SetConsoleCursorPosition(Handle, Pos);
}

void SetPixelColor(int x, int y, Color textColor, Color backColor)
{
	SetPoint(x, y);
	SetConsoleTextAttribute(Handle, textColor + (backColor << 4)); // backColor << 4는 backColor * 16과 같음
	printf("  ");
}

void SetScreenSize(int x, int y)
{
	system("mode con:cols=342 lines=128");
	for (int i = 0; i < 176; i++)
	{
		printf("%d", i % 10);
	}
	for (int i = 0; i < 128; i++)
	{
		//printf("%d\n", i);
	}
}