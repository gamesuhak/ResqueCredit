#include "Render.h"
#include "Color.h"
#define SPRITES_COUNT 10

enum Color
{
	COLOR_BLACK = 0, COLOR_DARKBLUE, COLOR_DARKGREEN, COLOR_DARKSKY, COLOR_DARKRED, COLOR_DARKPINK, COLOR_DARKYELLOW, COLOR_DARKWHITE,
	COLOR_GRAY, COLOR_BLUE, COLOR_GREEN, COLOR_SKY, COLOR_RED, COLOR_PINK, COLOR_YELLOW, COLOR_WHITE
};

struct Image
{
	int id;
	int width;
	int height;
	char** data;
};

// 게임 내에서 쓸 스프라이트 목록
Image *Sprites;

enum Sprite
{
	SPRITE_ = 0
};

// 화면 출력 함수
void Render()
{
	InitializeRender();

	for (int i = 0; i < SPRITES_COUNT; i++)
	{
		Sprites[i].id = i;
	}
}

void UpdateRender()
{

}

void InitializeRender()
{
	
	Sprites = malloc(sizeof(Image) * SPRITES_COUNT);
	SetScreenSize(176, 128);
}

void InitializeSprites()
{
	//Sprites = (Image*)malloc(sizeof(Image) * SPRITES_COUNT);
}

void RenderImage(int x, int y, Image* image)
{
	for (int posx = x; x < posx + image->width; x++)
	{
		for (int posy = y; y < posy + image->height; y++)
		{
			SetPixelColor(x, y, 0, image->data[posx][posy]);
		}
	}
}