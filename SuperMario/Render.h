#pragma once
#include <stdio.h>
#include "Image.h"
#include "Screen.h"
// Image.h에 선언된 사항
typedef struct Image Image;
typedef enum Sprite Sprite;
void Render();
void UpdateRender();
void InitializeRender();
void InitializeSprites();
void SetPixelColor(int x, int y, Color textColor, Color backColor);
void RenderImage(int x, int y, Image* image);