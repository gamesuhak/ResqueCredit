#include "Render.h"
#include <stdio.h>//
//#include "Image.h"//
#include "Screen.h"//
#include "FileLoader.h"
#include "Color.h"
#define SPRITES_COUNT 10

struct Image
{
	int id;
	int width;
	int height;
	int pivotx;
	int pivoty;
	Bitmap bitmap;
};

// 게임 내에서 쓸 스프라이트 목록
Image** Sprites;
Bitmap Screen;
Bitmap Buffer;
int PlayerX = 0;
int PlayerY = 0;

enum Sprite
{
	SPRITE_ = 0
};

// 화면 출력 함수
void Render()
{
	InitializeScreen();
	//printf("Render\n");
	InitializeRender();
	InitializeSprites();
	while (1)
	{
		/*
		if (++PlayerX >= 50)
		{
			PlayerX = 0;
		}*/
		UpdateRender();
	}
}

void UpdateRender()
{
	//printf("UpdateRender\n");
	AddImage(0, 0, Sprites[0], Buffer);
	AddImage(PlayerX, PlayerY, Sprites[1], Buffer);
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
		Sprites[i] = LoadBitmapFile("Player", COLOR_WHITE);
		Sprites[i]->pivotx = 0;
		Sprites[i]->pivoty = 0;
	}
	Sprites[0] = LoadBitmapFile("Map", COLOR_WHITE);
	Sprites[1] = LoadBitmapFile("Player", COLOR_WHITE);
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
			if (image->bitmap[posx][posy] < 0)
			{
				continue;
			}
			target[posx + x - image->pivotx][posy + y - image->pivoty] = image->bitmap[posx][posy];
		}
	}
}