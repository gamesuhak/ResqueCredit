#pragma once
#include "Image.h"

// Image.h에 선언된 사항
typedef struct Image Image;
typedef enum Sprite Sprite;
void Render();
void UpdateRender();
void InitializeRender();
void InitializeSprites();
void RenderImage(int x, int y, Image* image);
void AddImage(int x, int y, Image* image, Bitmap target);