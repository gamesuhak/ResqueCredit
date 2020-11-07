#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Color.h"
#include "Object.h"
#include "Bool.h"

// ���� ������ �� ��������Ʈ ���
Image** Sprites;
Bitmap Screen; // ���� ȭ�� �̹���
Bitmap Buffer; // 
Bitmap Transition;
bool isTransition;

extern Creature* Player;
extern Creature** Monsters;
extern Projectile** Projectiles;
extern int CreatureCount;
extern int ProjectileCount;

const char* SPRITENAME[SPRITES_COUNT] = {
	"Map",
	"FinnDown0", "FinnDown1", "FinnDown2",
	"FinnUp0", "FinnUp1", "FinnUp2",
	"FinnLeft0", "FinnLeft1", "FinnLeft2",
	"FinnRight0", "FinnRight1", "FinnRight2",
	"Monster"
};

// ȭ�� ��� �Լ�
void Render()
{
	InitializeScreen();
	InitializeRender();
	InitializeSprites();
	while (1)
	{
		UpdateAnimation();
		UpdateRender();
	}
}

// ȭ���� �����ϴ� �Լ�
void UpdateRender()
{
	AddImage(0, 0, Sprites[0], Buffer);
	AddImage(Player->object.position.x, Player->object.position.y, Sprites[1], Buffer);
	for (int i = 1; i < CreatureCount; i++)
	{
		// ������ id�� �ڽ��̰ų� ��Ȱ��ȭ ������ �� ��ŵ
		if (!Monsters[i]->enable)
		{
			continue;
		}
		AddImage(Monsters[i]->object.position.x, Monsters[i]->object.position.y, Sprites[2], Buffer);
	}
	for (int i = 0; i < ProjectileCount; i++)
	{
		// ������ id�� �ڽ��̰ų� ��Ȱ��ȭ ������ �� ��ŵ
		if (!Projectiles[i]->enable)
		{
			continue;
		}
		AddImage(Projectiles[i]->object.position.x, Projectiles[i]->object.position.y, Sprites[2], Buffer);
	}
	for (int posx = 0; posx < SCREEN_WIDTH; posx++)
	{
		for (int posy = 0; posy < SCREEN_HEIGHT; posy++)
		{
			if (Screen[posx][posy] == Buffer[posx][posy])
			{
				continue;
			}
			Screen[posx][posy] = Buffer[posx][posy];
			SetPixelColor(posx, posy, 0, Screen[posx][posy]);
		}
	}
}

// Render�� �ʱ�ȭ�ϴ� �Լ�
void InitializeRender()
{
	//printf("InitializeRender\n");
	Screen = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Sprites�� �ʱ�ȭ�ϴ� �Լ�
void InitializeSprites()
{
	Sprites = (Image**)malloc(sizeof(Image*) * SPRITES_COUNT);
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
	//RenderImage(0, 0, Sprites[1]);
}

// �̹����� ȭ�鿡 �׸��� �Լ�
void RenderImage(int x, int y, Image* image)
{
	for (int posx = 0; posx < image->width; posx++)
	{
		for (int posy = 0; posy < image->height; posy++)
		{
			SetPixelColor(posx + x - image->pivotx, posy + y - image->pivoty, 0, image->bitmap[posx][posy]);
		}
	}
}

// �̹����� �̹����� �׸��� �Լ�
void AddImage(int x, int y, Image* image, Bitmap target)
{
	for (int posx = 0; posx < image->width; posx++)
	{
		for (int posy = 0; posy < image->height; posy++)
		{
			if ((image->bitmap[posx][posy] < 0) || ((posx + x - image->pivotx < 0) || (posy + y - image->pivoty < 0)))
			{
				continue;
			}
			target[posx + x - image->pivotx][posy + y - image->pivoty] = image->bitmap[posx][posy];
		}
	}
}

void UpdateAnimation()
{

}