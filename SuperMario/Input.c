#include "Input.h"
#include <stdio.h>
#include <windows.h>
#include "Bool.h"

int KeyCode[KEY_COUNT]; // ���� �����Ǿ��ִ� Ű �ڵ带 �����ϴ� �迭
Bool KeyState[KEY_COUNT] = { False, False, False, False, False, False }; // Ű�� �����ִ� ���¸� ������ �迭
int KeyCharge[KEY_COUNT] = { 0, 0, 0, 0, 0, 0 }; // Ű�� �󸶳� �����ִ��� �����ϴ� �迭
const char* KeyName[KEY_COUNT] = { "��", "�Ʒ�", "����", "������", "A", "B" };

void Input()
{
	InitializeKey();
	while (1)
	{
		PushKey();
	}
}

void InitializeKey()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		KeyCharge[i] = 0;
	}
	BindKey();
}

void BindKey()
{
	KeyCode[KEY_UP] = VK_UP;
	KeyCode[KEY_DOWN] = VK_DOWN;
	KeyCode[KEY_LEFT] = VK_LEFT;
	KeyCode[KEY_RIGHT] = VK_RIGHT;
	KeyCode[KEY_A] = 0x5A;
	KeyCode[KEY_B] = 0x58;
	KeyCode[KEY_C] = 0x57;
}

void PushKey()
{
	Bool state;
	for (int i = 0; i < KEY_COUNT; i++)
	{
		state = False;
		if (GetAsyncKeyState(KeyCode[i]) < 0)
		{
			state = True;
		}
		if (KeyState[i] != state)
		{
			//printf("%sŰ�� ����Ǿ����ϴ�. : %s\n", KeyName[i], (TempKeyState[i] == 0 ? "False" : "True"));
			KeyState[i] = state;
			KeyCharge[i] = 0;
		}
		if (KeyState[i])
		{
			++KeyCharge[i];
		}
	}
}