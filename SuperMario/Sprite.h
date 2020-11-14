#pragma once
#define PIXELPERUNIT		8

typedef enum Sprite
{
	SPRITE_MAP = 0,
	SPRITE_PLAYER = 1,
	SPRITE_PLAYER_WALK = 17,
	SPRITE_MONSTER = 33,
	SPRITE_HEART = 34, SPRITE_HEART_HALF,

	SPRITE_TILE = 35,
	SPRITE_COUNT = 50
} Sprite;

void InitializeSprites();
void ParseSprite(int index, int column, int row);
void SetPivot(int index, int count, int pivot);