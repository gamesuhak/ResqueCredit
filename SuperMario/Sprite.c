#include "Sprite.h"

#include <stdio.h>
#include "Image.h"
#include "Object.h" // DIRECTION
#include "FileLoader.h" // LoadBitmapFile

// 게임 내에서 쓸 스프라이트 목록
Image** Sprites;

// 스프라이트의 이름들
const char* SPRITENAME[SPRITE_COUNT] =
{
	"Room",

	// 플레이어 스프라이트, 12개나 있는 이유는 첫번째 이미지를 잘라 12개로 사용하기 때문에
	"Player_Idle", "", "", "",
	"", "", "", "",
	"", "", "", "",
	"", "", "", "",

	"Player_Walk", "", "", "",
	"", "", "", "",
	"", "", "", "",
	"", "", "", "",

	"Monster",

	"UI", "UI", "Title",
};

// Sprites를 초기화하는 함수
void InitializeSprites()
{
	Sprites = (Image**)malloc(sizeof(Image*) * SPRITE_COUNT);
	if (Sprites == NULL) { return; }

	Sprites[SPRITE_MAP] = LoadBitmapFile(SPRITENAME[SPRITE_MAP], COLOR_WHITE);

	Sprites[SPRITE_PLAYER] = LoadBitmapFile(SPRITENAME[SPRITE_PLAYER], COLOR_GRAY);
	ParseSprite(SPRITE_PLAYER, 4, DIRECTION_COUNT);
	SetPivot(SPRITE_PLAYER, 4 * DIRECTION_COUNT, PIVOT_MIDDLE);

	Sprites[SPRITE_PLAYER_WALK] = LoadBitmapFile(SPRITENAME[SPRITE_PLAYER_WALK], COLOR_GRAY);
	ParseSprite(SPRITE_PLAYER_WALK, 4, DIRECTION_COUNT);
	SetPivot(SPRITE_PLAYER_WALK, 4 * DIRECTION_COUNT, PIVOT_MIDDLE);

	Sprites[SPRITE_MONSTER] = LoadBitmapFile(SPRITENAME[SPRITE_MONSTER], COLOR_YELLOW);

	Sprites[SPRITE_HEART] = LoadBitmapFile(SPRITENAME[SPRITE_HEART], COLOR_BLACK);

	Sprites[SPRITE_TITLE] = LoadBitmapFile(SPRITENAME[SPRITE_TITLE], COLOR_DARKSKY);
}

// 스프라이트를 분할하여 Sprites에 저장하는 메소드 
// index 분할할 스프라이트의 번호, column
void ParseSprite(int index, int column, int row)
{
	Image** images = SliceImage(Sprites[index], column, row);
	for (int i = 0; i < column * row; i++)
	{
		Sprites[index + i] = images[i];
		//printf("%d : %d\n", i, Sprites[index + i]->height);
	}
	free(images);
}

// 일괄적으로 Sprite의 중심점을 수정하는 메소드
// index 스프라이트의 첫 번호, count = 일괄적으로 변경할 개수, pivot = 열거형 Pivot의 값
void SetPivot(int index, int count, int pivot)
{
	for (int i = 0; i < count; i++)
	{
		if (pivot == PIVOT_LEFTUP)
		{
			Sprites[index + i]->pivot = NewCoordination(0, 0);
		}
		else if (pivot == PIVOT_MIDDLE)
		{
			Sprites[index + i]->pivot = NewCoordination(Sprites[index + i]->width >> 1, Sprites[index + i]->height >> 1);
			/*Sprites[index + i]->pivot.x = Sprites[index + i]->width >> 1;
			Sprites[index + i]->pivot.y = Sprites[index + i]->height >> 1;*/
		}
	}
}