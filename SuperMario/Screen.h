#pragma once
#include <Windows.h>
#include "Color.h"

// 화면 크기
#define SCREEN_WIDTH		88 // 화면 가로 픽셀 수
#define SCREEN_HEIGHT		64 // 화면 세로 픽셀 수

#define BUFFER_MAX			4
#define COMMAND_MAX			30

void InitializeScreen();
void RemoveScrollbar();
void SetScreenSize(int x, int y);
void SetPoint(int x, int y);
void SetPixelColor(int x, int y, Color textColor, Color backColor);
void ViewCursor(char value);