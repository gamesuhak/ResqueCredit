#include "Sprite.h"

#include <stdio.h>
#include "Image.h"
#include "Object.h" // DIRECTION
#include "FileLoader.h" // LoadBitmapFile

// ���� ������ �� ��������Ʈ ���
Image** Sprites;

// ��������Ʈ�� �̸���
const char* SPRITENAME[SPRITE_COUNT] =
{
	"Room",

	// �÷��̾� ��������Ʈ, 12���� �ִ� ������ ù��° �̹����� �߶� 12���� ����ϱ� ������
	"Player_Idle", "", "", "",
	"", "", "", "",
	"", "", "", "",
	"", "", "", "",

	"Player_Walk", "", "", "",
	"", "", "", "",
	"", "", "", "",
	"", "", "", "",

	"Kirby",

	"UI", "", "",
	
	"Bullet",
	
	"Arrow",
	"",
	"",
	"",

	"Sword",
	"Sword",
	"Sword",
	"Sword",

	"Title",

	"Tile", "","","",
	"","","","",
	"","","","",
	"","","","",
	"","","","",
	"","","","",
	"","","","",
	"","","","",

	"Bubblun",
	"Crew",
	"Ghost",
	"Clear",
	"GameOver"
};

// Sprites�� �ʱ�ȭ�ϴ� �Լ�
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
	
	Sprites[SPRITE_BULLET] = LoadBitmapFile(SPRITENAME[SPRITE_BULLET], COLOR_BLACK);
	SetPivot(SPRITE_BULLET, 1, PIVOT_MIDDLE);
	
	Sprites[SPRITE_ARROW] = LoadBitmapFile(SPRITENAME[SPRITE_ARROW], COLOR_BLACK);
	ParseSprite(SPRITE_ARROW, 1, DIRECTION_COUNT);
	SetPivot(SPRITE_ARROW, DIRECTION_COUNT, PIVOT_MIDDLE);

	Sprites[SPRITE_SWORD] = LoadBitmapFile(SPRITENAME[SPRITE_SWORD], COLOR_BLACK);
	ParseSprite(SPRITE_SWORD, 1, DIRECTION_COUNT);
	SetPivot(SPRITE_SWORD, DIRECTION_COUNT, PIVOT_MIDDLE);

	

	Sprites[SPRITE_HEART] = LoadBitmapFile(SPRITENAME[SPRITE_HEART], COLOR_BLACK);
	ParseSprite(SPRITE_HEART, 3, 1);

	Sprites[SPRITE_TITLE] = LoadBitmapFile(SPRITENAME[SPRITE_TITLE], COLOR_DARKSKY);

	Sprites[SPRITE_TILE] = LoadBitmapFile(SPRITENAME[SPRITE_TILE], COLOR_PINK);
	ParseSprite(SPRITE_TILE, 4, 8);

	Sprites[SPRITE_TILE] = LoadBitmapFile(SPRITENAME[SPRITE_TILE], COLOR_PINK);

	Sprites[SPRITE_KIRBY] = LoadBitmapFile(SPRITENAME[SPRITE_KIRBY], COLOR_YELLOW);
	SetPivot(SPRITE_KIRBY, 1, PIVOT_MIDDLE);
	Sprites[SPRITE_BUBBLUN] = LoadBitmapFile(SPRITENAME[SPRITE_BUBBLUN], COLOR_DARKPINK);
	Sprites[SPRITE_CREW] = LoadBitmapFile(SPRITENAME[SPRITE_CREW], COLOR_DARKPINK);
	Sprites[SPRITE_GHOST] = LoadBitmapFile(SPRITENAME[SPRITE_GHOST], COLOR_DARKPINK);
	SetPivot(SPRITE_BUBBLUN, 3, PIVOT_MIDDLE);

	Sprites[SPRITE_CLEAR] = LoadBitmapFile(SPRITENAME[SPRITE_CLEAR], COLOR_DARKYELLOW);
	Sprites[SPRITE_GAMEOVER] = LoadBitmapFile(SPRITENAME[SPRITE_GAMEOVER], COLOR_DARKGREEN);
}

// ��������Ʈ�� �����Ͽ� Sprites�� �����ϴ� �޼ҵ� 
// index ������ ��������Ʈ�� ��ȣ, column
void ParseSprite(int index, int column, int row)
{
	Image** images = SliceImage(Sprites[index], column, row);
	for (int i = 0; i < column * row; i++)
	{
		Sprites[index + i] = images[i];
		//printf("%d : %d\n", index + i, Sprites[index + i]->height);
	}
	free(images);
}

// �ϰ������� Sprite�� �߽����� �����ϴ� �޼ҵ�
// index ��������Ʈ�� ù ��ȣ, count = �ϰ������� ������ ����, pivot = ������ Pivot�� ��
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
		}
	}
}