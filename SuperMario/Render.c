#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Sprite.h"
#include "Color.h"
#include "Animator.h"
#include "Bool.h"
#include "Map.h"

Image* Screen; // ���� ȭ�� �̹���
Image* Buffer; // ���� ȭ�� �׸��� ���� �׸��� ����

Image* BufferRoom;

extern Stage* Stage1;
extern Coordination PlayerRoom;

extern Image** Sprites;

extern Creature* Player;
extern Creature** Monsters;
extern Projectile** Projectiles;
extern int CreatureCount;
extern int ProjectileCount;

// ȭ�� ��� �Լ�
void Render()
{
	InitializeScreen();
	InitializeSprites();
	InitializeRender();
	while (1)
	{
		/*for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				RenderImage(x * 8 + 4, y * 8 + 4, Sprites[SPRITE_FINN + (y * 3) + x]);
			}
		}*/
		//UpdateAnimation();

		/*Stage1 = NewStage();
		RenderStage(0, 0, Stage1);
		Sleep(1000);*/
		UpdateRender();
	}
}

// Render�� �ʱ�ȭ�ϴ� �Լ�
void InitializeRender()
{
	Screen = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);
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
			SetPixelColor(posx, posy, COLOR_BLACK, Screen->bitmap[posx][posy]);
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

void RenderStage(int x, int y, Stage* stage)
{
	for (int posx = 0; posx < stage->width; posx++)
	{
		for (int posy = 0; posy < stage->height; posy++)
		{
			if (stage->roomData[posx][posy] > -1)
				SetPixelColor(posx + x, posy + y, 0, stage->roomData[posx][posy] + 6);
			else
				SetPixelColor(posx + x, posy + y, 0, COLOR_BLACK);
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
