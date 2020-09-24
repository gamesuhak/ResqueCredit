#include "Input.h"
#include <stdio.h>
#include <windows.h>
#include <Winuser.h>
#include <stdlib.h>
#include "Bool.h"

int KeyCode[KEY_COUNT]; // 현재 설정되어있는 키 코드를 저장하는 배열
bool KeyState[KEY_COUNT] = { false, false, false, false, false, false }; // 키가 눌려있는 상태를 저장할 배열
bool TempKeyState[KEY_COUNT] = { false, false, false, false, false, false }; // 임시로 키의 상태를 저장할 배열
char* KeyName[KEY_COUNT] = { "위", "아래", "왼쪽", "오른쪽", "A", "B" };
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
			//printf("%s키가 변경되었습니다. : %s\n", KeyName[i], (TempKeyState[i] == 0 ? "false" : "true"));
			KeyState[i] = TempKeyState[i];
			KeyCharge[i] = 0;
		}
		
		if (KeyState[i])
		{
			//printf("%s키 차징 값 : %f\n", KeyName[i], (++KeyCharge[i] * 0.01));
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