#pragma once
#define PIXELPERUNIT		8

typedef enum Sprite
{
	SPRITE_MAP = 0,

	SPRITE_PLAYER = 1,
	SPRITE_PLAYER_WALK = 17,
	SPRITE_KIRBY = 33,
	SPRITE_HEART = 34, SPRITE_HEART_HALF, SPRITE_HEART_NOT,

	SPRITE_BULLET = 37,
	SPRITE_ARROW,
	SPRITE_SWORD = 42,

	SPRITE_TITLE = 46,
	SPRITE_TILE = 47,

	SPRITE_BUBBLUN = 79,
	SPRITE_CREW,
	SPRITE_GHOST,
	SPRITE_CLEAR,
	SPRITE_GAMEOVER,
	SPRITE_COUNT = 100
} Sprite;

void InitializeSprites();
void ParseSprite(int index, int column, int row);
void SetPivot(int index, int count, int pivot);