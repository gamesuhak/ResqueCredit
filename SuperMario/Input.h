#pragma once
#include "Bool.h"

typedef enum Key
{
	KEY_UP = 0, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
	KEY_A, KEY_B, KEY_C, KEY_COUNT
} Key;

void InputProcess();
void InitializeKey();
void BindKey();
void PushKey();
void SetInputHandler(void (*method)());
Bool PressAnyKey();