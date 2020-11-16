#include "Screen.h"
#include <stdio.h>
#include "Bool.h"
#include "Image.h"

extern Image* Screen;

// ȭ�� ������ ������ �ִ� �ڵ��� ������ ����
HANDLE Handle;

char ASCIIMODE = False;
const char* ASCIIColor[COLOR_COUNT] = { "  ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" };

void InitializeScreen()
{
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTitle("Title");
	SetScreenSize(SCREEN_WIDTH << 1, SCREEN_HEIGHT); // ������ ���� ũ��� �ȼ� * 2�̴�
	RemoveScrollbar();
	ViewCursor(0);
}

// �����̴� Ŀ�� ����� �޼ҵ�
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
	if (ASCIIMODE)
	{
		SetConsoleTextAttribute(Handle, COLOR_WHITE);
		printf("%s", ASCIIColor[backColor]);
		//printf("%c%c", 97 + backColor, 97 + backColor);
	}
	else
	{
		SetConsoleTextAttribute(Handle, textColor + (backColor << 4)); // backColor << 4�� backColor * 16�� ����
		printf("  ");
	}
}

void PrintText(int x, int y, char* string, Color textColor)
{
	char text[3] = "";//�����ڵ�� 2���� �ڵ尪���� �̷���� �����Ƿ� 2�� ����, 1���� �ι��ڸ� �������
	SetPoint(x, y);
	for (int i = 0; i < strlen(string); i++)//�� ���̸�ŭ �ݺ�
	{
		SetConsoleTextAttribute(Handle, textColor + (Screen->bitmap[x + (i >> 1)][y] << 4)); // backColor << 4�� backColor * 16�� ����

		if (string[i] < 0)
		{
			strncpy(text, string + i++, 2);//�ڵ� 2���� text�� ����, ó���� ������ i�� 1������
		}
		else
		{
			text[0] = string[i];//�ش� �ڵ带 text[0]�� ����
			text[1] = '\0';//�ڵ� �ڿ� �ι��ڸ� ����
		}
		printf("%s", text);//text�� ����ִ� ���ڸ� ���
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