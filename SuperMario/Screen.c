#include "Screen.h"
//#include "Color.h"
#define SCREEN_WIDTH	176
#define SCREEN_HEIGHT	64
#define BUFFER_MAX		4
#define COMMAND_MAX		30

// 화면 정보를 가지고 있는 핸들을 저장할 변수
HANDLE Handle;

void InitializeScreen()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("Title");
	//system("cls");
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

void SetScreenSize(int width, int height)
{
	char command[COMMAND_MAX] = "mode con:cols=";
	char buffer[BUFFER_MAX] = "";

	sprintf(buffer, "%d", width);
	strcat(command, buffer);
	strcat(command, " lines=");
	sprintf(buffer, "%d", height);
	strcat(command, buffer);

	system(command);
	//system("mode con:cols=176 lines=64");
}