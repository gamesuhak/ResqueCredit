#pragma once
typedef enum Key
{
	KEY_UP = 0, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
	KEY_A, KEY_B, KEY_COUNT
} Key;
void BindKey();
void PushKey();
int Input();