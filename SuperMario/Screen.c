#include "Screen.h"
#include <stdio.h>
#include "Bool.h"
#include "Image.h"

extern Image* Screen;

// 화면 정보를 가지고 있는 핸들을 저장할 변수
HANDLE Handle;

char ASCIIMODE = False;
const char* ASCIIColor[COLOR_COUNT] = { "  ", "■", "♣", "＠", "▒", "▤", "▥", "▨", "▩", "♨", "☏", "♥", "♠", "★", "▣", "◈" };

void InitializeScreen()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTitle("Title");
	SetScreenSize(SCREEN_WIDTH << 1, SCREEN_HEIGHT); // 가로의 실제 크기는 픽셀 * 2이다
	RemoveScrollbar();
	ViewCursor(0);
}

// 깜빡이는 커서 숨기는 메소드
void ViewCursor(char value)
{
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = value;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(Handle, &ConsoleCursor);
} // 참고 : https://blog.naver.com/upssuyo/80092210109

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
	if (backColor < 0)
	{
		return;
	}
	SetPoint(x, y);
	if (ASCIIMODE)
	{
		SetConsoleTextAttribute(Handle, COLOR_WHITE);
		printf("%s", ASCIIColor[backColor]);
		//printf("%c%c", 97 + backColor, 97 + backColor);
	}
	else
	{
		SetConsoleTextAttribute(Handle, textColor + (backColor << 4)); // backColor << 4는 backColor * 16과 같음
		printf("  ");
	}
}

void PrintText(int x, int y, char* string, Color textColor)
{
	char text[3] = "";//유니코드는 2개의 코드값으로 이루어져 있으므로 2개 저장, 1개는 널문자를 담기위함
	SetPoint(x, y);
	for (int i = 0; i < strlen(string); i++)//총 길이만큼 반복
	{
		SetConsoleTextAttribute(Handle, textColor + (Screen->bitmap[x + (i >> 1)][y] << 4)); // backColor << 4는 backColor * 16과 같음

		if (string[i] < 0)
		{
			strncpy(text, string + i++, 2);//코드 2개를 text에 복사, 처리가 끝난뒤 i을 1더해줌
		}
		else
		{
			text[0] = string[i];//해당 코드를 text[0]에 대입
			text[1] = '\0';//코드 뒤에 널문자를 대입
		}
		printf("%s", text);//text에 들어있는 문자를 출력
	}
}

void EraseText(int x, int y, int count)
{
	SetPoint(x, y);
	for (int i = 0; i < count; i++)
	{
		if (x + i >= SCREEN_WIDTH)
		{
			break;
		}
		SetPixelColor(x + i, y, COLOR_BLACK, Screen->bitmap[x + i][y]);
	}
}