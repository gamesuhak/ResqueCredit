#pragma once
#include "Image.h"
#define SPRITES_COUNT	10

typedef enum Sprite
{
	SPRITE_FIN_DOWN_0 = 0
} Sprite;
//const char* SPRITENAME[SPRITES_COUNT] = { "FinnDown0", "FinnDown1", "FinnDown2"  };
void Render();
void CheckRender();
void UpdateRender();
void InitializeRender();
void InitializeSprites();
void RenderImage(int x, int y, Image* image);
void AddImage(int x, int y, Image* image, Bitmap target);