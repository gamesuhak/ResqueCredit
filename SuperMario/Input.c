#include "Input.h"
#include <stdio.h>
#include <windows.h>
#include <Winuser.h>
#include <stdlib.h>
#include "Bool.h"

int KeyCode[KEY_COUNT]; // ���� �����Ǿ��ִ� Ű �ڵ带 �����ϴ� �迭
bool KeyState[KEY_COUNT] = { false, false, false, false, false, false }; // Ű�� �����ִ� ���¸� ������ �迭
bool TempKeyState[KEY_COUNT] = { false, false, false, false, false, false }; // �ӽ÷� Ű�� ���¸� ������ �迭
char* KeyName[KEY_COUNT] = { "��", "�Ʒ�", "����", "������", "A", "B" };
int KeyCharge[KEY_COUNT] = { 0, 0, 0, 0, 0, 0 };

void BindKey()
{
	KeyCode[KEY_UP] = VK_UP;
	KeyCode[KEY_DOWN] = VK_DOWN;
	KeyCode[KEY_LEFT] = VK_LEFT;
	KeyCode[KEY_RIGHT] = VK_RIGHT;
	KeyCode[KEY_A] = 0x5A;
	KeyCode[KEY_B] = 0x58;
}

void PushKey()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		TempKeyState[i] = false;
		//if (GetAsyncKeyState(KeyCode[i]) & 0x0001)
		if (GetAsyncKeyState(KeyCode[i]) < 0)
		{
			TempKeyState[i] = true;
		}
		if (KeyState[i] != TempKeyState[i])
		{
			//printf("%sŰ�� ����Ǿ����ϴ�. : %s\n", KeyName[i], (TempKeyState[i] == 0 ? "false" : "true"));
			KeyState[i] = TempKeyState[i];
			KeyCharge[i] = 0;
		}
		
		if (KeyState[i])
		{
			//printf("%sŰ ��¡ �� : %f\n", KeyName[i], (++KeyCharge[i] * 0.01));
		}
	}
}

int Input()
{
	BindKey();
	while (1)
	{
		PushKey();
	};
}