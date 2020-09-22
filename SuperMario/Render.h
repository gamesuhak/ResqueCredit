#pragma once
//#include <stdio.h>
#include "Image.h"
//#include "Screen.h"

// Image.h�� ����� ����
typedef struct Image Image;

typedef enum Sprite Sprite;
void Render();
void UpdateRender();
void InitializeRender();
void InitializeSprites();
void RenderImage(int x, int y, Image* image);
void AddImage(int x, int y, Image* image, Bitmap target);