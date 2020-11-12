#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Color.h"
#include "Animator.h"
#include "Bool.h"

// ���� ������ �� ��������Ʈ ���
Image** Sprites;
Image* Screen; // ���� ȭ�� �̹���
Image* Buffer; // ���� ȭ�� �׸��� ���� �׸��� ����

//Image* CurrentRoom;
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

	// �÷��̾� ��������Ʈ, 12���� �ִ� ������ ù��° �̹����� �߶� 12���� ����ϱ� ������
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",

	"Monster",

	"UI", "UI", "UI",
};

// ȭ�� ��� �Լ�
void Render()
{
	InitializeScreen();
	InitializeRender();
	InitializeSprites();
	RenderImage(0, 0, Sprites[SPRITE_MAP]);
	while (1)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				RenderImage(x * 8, y * 8, Sprites[SPRITE_FINN + (y * 3) + x]);
			}
		}
		
		//UpdateAnimation();
		//UpdateRender();
	}
}

// Render�� �ʱ�ȭ�ϴ� �Լ�
void InitializeRender()
{
	Screen = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);//NewArray(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);//NewArray(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Sprites�� �ʱ�ȭ�ϴ� �Լ�
void InitializeSprites()
{
	Sprites = (Image**)malloc(sizeof(Image*) * SPRITE_COUNT);
	if (Sprites == NULL) { return; }

	Sprites[SPRITE_MAP] = LoadBitmapFile(SPRITENAME[SPRITE_MAP], COLOR_WHITE);
	Sprites[SPRITE_FINN] = LoadBitmapFile(SPRITENAME[SPRITE_FINN], COLOR_GRAY);
	ParseSprite(SPRITE_FINN, 3, DIRECTION_COUNT);
	SetPivot(SPRITE_FINN, 3 * DIRECTION_COUNT, PIVOT_MIDDLE);

	Sprites[SPRITE_MONSTER] = LoadBitmapFile(SPRITENAME[SPRITE_MONSTER], COLOR_YELLOW);

	Sprites[SPRITE_HEART] = LoadBitmapFile(SPRITENAME[SPRITE_HEART], COLOR_BLACK);

}

// ȭ���� �����ϴ� �Լ�
// ����� ���̾ / Y�� �������� ���ĵǾ�ߵ�
void UpdateRender()
{
	UpdateUI(Buffer); // UI ������Ʈ
	//RenderMap(CurrentRoom, Buffer);

	for (int posx = 0; posx < SCREEN_WIDTH; posx++)
	{
		for (int posy = 0; posy < SCREEN_HEIGHT; posy++)
		{
			if (Screen->bitmap[posx][posy] == Buffer->bitmap[posx][posy]) { continue; }
			Screen->bitmap[posx][posy] = Buffer->bitmap[posx][posy];
			SetPixelColor(posx, posy, 0, Screen->bitmap[posx][posy]);
		}
	}
}

void RenderMap(Room* room, Image* target)
{
	AddImage(0, 0, Sprites[SPRITE_MAP], target);
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			AddImage(x * PIXELPERUNIT, y * PIXELPERUNIT, Sprites[SPRITE_TILE + room->tile[x][y]], target);
		}
	}

	for (int layer = 0; layer < LAYER_COUNT; layer++)
	{
		
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

void RenderImage(int x, int y, Image* image)
{
	for (int posx = 0; posx < image->width; posx++)
	{
		for (int posy = 0; posy < image->height; posy++)
		{
			SetPixelColor(posx + x - image->pivot.x, posy + y - image->pivot.y, 0, image->bitmap[posx][posy]);
		}
	}
}

// UI�� �׸��� �޼ҵ�
void UpdateUI(Image* target)
{
	// ������ ��Ʈ�� ������ hp���� 1�� ��Ʈ�� ���� ������ / 2�� ���
	int hpCount = (Player->hp ^ 1) >> 1;

	// ������ ��Ʈ�� ������ŭ ���� ��ܿ������� �������� �׸�
	for (int i = 0; i < hpCount; i++)
	{
		AddImage(i * PIXELPERUNIT, 0, Sprites[SPRITE_HEART], target);
	}

	//HP�� Ȧ���� ��
	if (Player->hp & 1)
	{
		AddImage((hpCount + 1) * PIXELPERUNIT, 0, Sprites[SPRITE_HEART_HALF], target);
	}
}

void UpdateAnimation()
{

}

// ��������Ʈ�� �����Ͽ� Sprites�� �����ϴ� �޼ҵ� 
// index ������ ��������Ʈ�� ��ȣ, column
void ParseSprite(int index, int column, int row)
{
	Image** images = SliceImage(Sprites[index], column, row);
	for (int i = 0; i < column * row; i++)
	{
		Sprites[index + i] = images[i];
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
			Sprites[index + i]->pivot.x = 0;
			Sprites[index + i]->pivot.y = 0;
		}
		else if (pivot == PIVOT_MIDDLE)
		{
			Sprites[index + i]->pivot.x = Sprites[index + i]->width >> 1;
			Sprites[index + i]->pivot.y = Sprites[index + i]->height >> 1;
		}
	}
}