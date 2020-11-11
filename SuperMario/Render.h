#pragma once
#include "Image.h"
#include "Map.h"

#define PIXELPERUNIT		16
#define UI_X				0
#define UI_Y				0
#define UI_WIDTH			48
#define UI_HEIGHT			16
#define CAMERA_X			16
#define CAMERA_Y			0
#define CAMERA_WIDTH		

typedef enum Sprite
{
	SPRITE_MAP = 0,
	SPRITE_FINN = 1, SPRITE_FINN_DOWN_1, SPRITE_FINN_DOWN_2, 
	SPRITE_FINN_LEFT_0,
	SPRITE_MONSTER = 13,
	SPRITE_HEART = 14, SPRITE_HEART_HALF,

	SPRITE_TILE = 16,
	SPRITE_COUNT = 20
} Sprite;

void Render();
void UpdateRender();
void InitializeRender();
void InitializeSprites();

void RenderMap(Room* room, Image* target);
void RenderImage(int x, int y, Image* image);
void UpdateUI(Image* target);
void UpdateAnimation();

void ParseSprite(int index, int column, int row);
void SetPivot(int index, int count, int pivot);