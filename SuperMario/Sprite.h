#pragma once
#define PIXELPERUNIT		16

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

void InitializeSprites();
void ParseSprite(int index, int column, int row);
void SetPivot(int index, int count, int pivot);