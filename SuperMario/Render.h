#pragma once
#include "Image.h"
#define SPRITES_COUNT	20

#define UI_X			0
#define UI_Y			0
#define UI_WIDTH		48
#define UI_HEIGHT		16
#define CAMERA_X		16
#define CAMERA_Y		0
typedef enum Sprite
{
	SPRITE_MAP = 0,
	SPRITE_FINN = 1, SPRITE_FIN_DOWN_1, SPRITE_FIN_DOWN_2, 
	SPRITE_MONSTER = 13,

} Sprite;

void Render();
void UpdateRender();
void InitializeRender();
void InitializeSprites();
void RenderImage(int x, int y, Image* image);
void AddImage(int x, int y, Image* image, Bitmap target);
void UpdateAnimation();
void UpdateUI();
void RenderCamera();