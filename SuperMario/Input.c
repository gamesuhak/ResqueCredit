#include "Input.h"

#include <windows.h>
#include "GameData.h"

extern SceneType Scene;

int KeyCode[KEY_COUNT]; // 현재 설정되어있는 키 코드를 저장하는 배열
Bool KeyState[KEY_COUNT] = { False, False, False, False, False, False }; // 키가 눌려있는 상태를 저장할 배열
int KeyCharge[KEY_COUNT] = { 0, 0, 0, 0, 0, 0 }; // 키가 얼마나 눌려있는지 저장하는 배열
const char* KeyName[KEY_COUNT] = { "위", "아래", "왼쪽", "오른쪽", "A", "B" };
void (*InputHandler)() = NULL; // 키를 눌렀을 때 실행할 메소드를 저장하는 포인터

void InputProcess()
{
	while (Scene != SCENE_GAMEOVER && Scene != SCENE_CLEAR)
	{
		PushKey();
		if (InputHandler == NULL) { continue; }
		InputHandler();
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
			KeyState[i] = state;
			//printf("%s키가 변경되었습니다. : %s\n", KeyName[i], (KeyState[i] == True ? "True" : "False"));
			KeyCharge[i] = 0;
		}
		if (KeyState[i])
		{
			++KeyCharge[i];
		}
	}
}

void SetInputHandler(void (*method)())
{
	InputHandler = method;
	InputHandler(); // 왜인지는 모르겠지만 한번 호출해주지 않으면 영원히 실행되지 않음
	return;
}


// 아무키나 눌려있으면 True반환
Bool PressAnyKey()
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		if (KeyState[i]) { return True; }
	}
	return False;
}