#pragma once
#include <Windows.h>
#include "Color.h"
#define SCREEN_WIDTH	176
#define SCREEN_HEIGHT	64
#define BUFFER_MAX		4
#define COMMAND_MAX		30

void InitializeScreen();
void RemoveScrollbar();
void SetScreenSize(int x, int y);
void SetPoint(int x, int y);
void SetPixelColor(int x, int y, Color textColor, Color backColor);
void ViewCursor(char value);