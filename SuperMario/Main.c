#include <stdio.h>
#include <Windows.h>

// �ڷ��� bool�� ����� �� �ֵ��� ���� �� ����
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