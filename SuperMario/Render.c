#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Color.h"
#include "Object.h"
#include "Bool.h"

// 게임 내에서 쓸 스프라이트 목록
Image** Sprites;
Bitmap Screen;
Bitmap Buffer;
extern Creature* Player;
extern Creature** Monsters;
extern int CreatureCount;

// 화면 출력 함수
void Render()
{
	InitializeScreen();
	//printf("Render\n");
	InitializeRender();
	InitializeSprites();
	while (1)
	{
		UpdateRender();
	}
}

void CheckRender()
{
	for (int i = 0; i <= COLOR_WHITE; i++)
	{
		SetPixelColor(i, 0, 0, i);
	}
}

void UpdateRender()
{
	//printf("UpdateRender\n");
	AddImage(0, 0, Sprites[0], Buffer);
	AddImage(Player->object.position.x, Player->object.position.y, Sprites[1], Buffer);
	for (int i = 0; i < CreatureCount - 1; i++)
	{
		// 몬스터의 id가 자신이거나 비활성화 돼있을 때 스킵
		if (Monsters[i]->id == 0 || !Monsters[i]->enable)
		{
			continue;
		}
		AddImage(Monsters[i]->object.position.x, Monsters[i]->object.position.y, Sprites[2], Buffer);
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

void InitializeRender()
{
	//printf("InitializeRender\n");
	Screen = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void InitializeSprites()
{
	Sprites = (Image**)malloc(sizeof(Image*) * SPRITES_COUNT);
	if (Sprites == NULL) { return; }
	for (int i = 0; i < SPRITES_COUNT; i++)
	{
		Sprites[i] = LoadBitmapFile("FinnDown0", COLOR_WHITE);
		Sprites[i]->pivotx = 4;
		Sprites[i]->pivoty = 4;
	}
	Sprites[0] = LoadBitmapFile("Map", COLOR_WHITE);
	Sprites[1] = LoadBitmapFile("FinnDown0", COLOR_GRAY);
	Sprites[1]->pivotx = 4;
	Sprites[1]->pivoty = 4;
	Sprites[2] = LoadBitmapFile("Monster", COLOR_YELLOW);
	Sprites[2]->pivotx = 4;
	Sprites[2]->pivoty = 4;
	//RenderImage(0, 0, Sprites[1]);
}

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