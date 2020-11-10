#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Color.h"
#include "Object.h"
#include "Map.h"
#include "Animator.h"
#include "Bool.h"

// ���� ������ �� ��������Ʈ ���
Image** Sprites;
Bitmap Screen; // ���� ȭ�� �̹���
Bitmap Buffer; // ���� ȭ�� �׸��� ���� �׸��� ����

Bitmap BufferRoom;

Image* CurrentRoom;
Image* BufferRoom;

extern int PlayerMapX;
extern int PlayerMapY;

extern Creature* Player;
extern Creature** Monsters;
extern Projectile** Projectiles;
extern int CreatureCount;
extern int ProjectileCount;

// ��������Ʈ�� �̸���
const char* SPRITENAME[SPRITE_COUNT] = {
	"Map",
	"FinnDown0", "FinnDown1", "FinnDown2",
	"FinnUp0", "FinnUp1", "FinnUp2",
	"FinnLeft0", "FinnLeft1", "FinnLeft2",
	"FinnRight0", "FinnRight1", "FinnRight2",
	"Monster",

	"UI_Heart",
	"UI_Heart_Half",
};

// ȭ�� ��� �Լ�
void Render()
{
	InitializeScreen();
	InitializeRender();
	InitializeSprites();
	while (1)
	{
		
		if (0)
		{

		}
		else
		{
			UpdateAnimation();
			UpdateRender();
		}
		
	}
}

// Render�� �ʱ�ȭ�ϴ� �Լ�
void InitializeRender()
{
	Screen = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Sprites�� �ʱ�ȭ�ϴ� �Լ�
void InitializeSprites()
{
	Sprites = (Image**)malloc(sizeof(Image*) * SPRITE_COUNT);
	if (Sprites == NULL) { return; }

	Sprites[0] = LoadBitmapFile(SPRITENAME[SPRITE_MAP], COLOR_WHITE);
	for (int i = 0; i < 1; i++)
	{
		Sprites[i] = LoadBitmapFile(SPRITENAME[SPRITE_MAP], COLOR_WHITE);
		Sprites[i]->pivotx = 4;
		Sprites[i]->pivoty = 4;
	}
	
	Sprites[1] = LoadBitmapFile(SPRITENAME[SPRITE_FINN], COLOR_GRAY);
	Sprites[1]->pivotx = 4;
	Sprites[1]->pivoty = 4;
	Sprites[2] = LoadBitmapFile(SPRITENAME[SPRITE_MONSTER], COLOR_YELLOW);
	Sprites[2]->pivotx = 4;
	Sprites[2]->pivoty = 4;

	Sprites[SPRITE_HEART] = LoadBitmapFile(SPRITENAME[SPRITE_HEART], COLOR_BLACK);
	//RenderImage(0, 0, Sprites[1]);
}

// ȭ���� �����ϴ� �Լ�
// ����� ���̾ / Y�� �������� ���ĵǾ�ߵ�
void UpdateRender()
{
	UpdateUI(); // UI ������Ʈ
	//RenderMap(, );

	for (int posx = 0; posx < SCREEN_WIDTH; posx++)
	{
		for (int posy = 0; posy < SCREEN_HEIGHT; posy++)
		{
			if (Screen[posx][posy] == Buffer[posx][posy]) { continue; }
			Screen[posx][posy] = Buffer[posx][posy];
			SetPixelColor(posx, posy, 0, Screen[posx][posy]);
		}
	}
}

void RenderMap(Room* room, Image* target)
{
	for (int y; y < room->height; y++)
	{
		for (int x; x < room->width; x++)
		{
			AddImage(x * PIXELPERUNIT, y * PIXELPERUNIT, Sprites[SPRITE_TILE + room->tile[x][y]], CurrentRoom)
		}
	}

	for (int layer; layer < LAYER_COUNT; layer++)
	{
		AddImage(0, 0, Sprites[0], target);
		AddImage(Player->object.position.x, Player->object.position.y, Sprites[1], target);
		for (int i = 1; i < CreatureCount; i++)
		{
			// ���Ͱ� ��Ȱ��ȭ ������ �� ����
			if (!Monsters[i]->enable) { continue; }

			AddImage(Monsters[i]->object.position.x, Monsters[i]->object.position.y, Sprites[2], target);
		}
		for (int i = 0; i < ProjectileCount; i++)
		{
			// ����ü�� ��Ȱ��ȭ ������ �� ����
			if (!Projectiles[i]->enable) { continue; }

			AddImage(Projectiles[i]->object.position.x, Projectiles[i]->object.position.y, Sprites[2], target);
		}
	}
}

// UI�� �׸��� �޼ҵ�
void UpdateUI()
{
	// ������ ��Ʈ�� ������ hp���� 1�� ��Ʈ�� ���� ������ / 2�� ���
	int hpCount = (Player->hp ^ 1) >> 1;

	// ������ ��Ʈ�� ������ŭ ���� ��ܿ������� �������� �׸�
	for (int i = 0; i < hpCount; i++)
	{
		AddImage(i * PIXELPERUNIT, 0, Sprites[SPRITE_HEART], Buffer);
	}

	//HP�� Ȧ���� ��
	if (Player->hp & 1)
	{
		AddImage((hpCount + 1) * PIXELPERUNIT, 0, Sprites[SPRITE_HEART_HALF], Buffer);
	}
}


void UpdateAnimation()
{

}