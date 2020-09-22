#pragma once
#include <stdio.h>
#include "Image.h"
#include "Screen.h"

// Image.h에 선언된 사항
typedef struct Image Image;
typedef enum Sprite Sprite;
void Render();
void InitializeRender();
void SetPoint(int x, int y);
void SetPixelColor(int x, int y, Color textColor, Color backColor);
void DrawImage(int x, int y, Image* image);
void SetScreenSize(int x, int y);