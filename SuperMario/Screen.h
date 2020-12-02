#pragma once
#include <Windows.h>
#include "Color.h"
#include "Image.h"

// ȭ�� ũ��
#define SCREEN_WIDTH		88 // ȭ�� ���� �ȼ� ��
#define SCREEN_HEIGHT		64 // ȭ�� ���� �ȼ� ��

#define BUFFER_MAX			4
#define COMMAND_MAX			30

typedef enum TextAlign { TEXT_LEFT, TEXT_MIDDLE, TEXT_RIGHT } TextAlign;

void InitializeScreen();
void RemoveScrollbar();
void SetScreenSize(int x, int y);
void SetPoint(int x, int y);
void SetPixelColor(int x, int y, Color textColor, Color backColor);
void ViewCursor(char value);
void SetScreenImage(Image* image);
void PrintText(int x, int y, char* string, Color textColor, TextAlign align);
void EraseText(int x, int y, int count);