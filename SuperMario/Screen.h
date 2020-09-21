#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Color.h"

void InitializeScreen();
void SetPoint(int x, int y);
void SetPixelColor(int x, int y, Color textColor, Color backColor);
void SetScreenSize(int x, int y);
void RemoveScrollbar();