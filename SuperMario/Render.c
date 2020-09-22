
#include "Render.h"
#include "FileLoader.h"
#include "Color.h"
#define SPRITES_COUNT		10
#define SPRITES_NAME_MAX	20

enum Color
{
	COLOR_TRANSPARENT = -1, COLOR_BLACK, COLOR_DARKRED, COLOR_DARKGREEN, COLOR_DARKYELLOW, COLOR_DARKBLUE, COLOR_DARKPINK, COLOR_DARKSKY, COLOR_GRAY,
	COLOR_DARKWHITE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_PINK, COLOR_SKY, COLOR_WHITE
};

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
char SpriteName[SPRITES_COUNT][SPRITES_NAME_MAX] = {
	"Player", "Player", "Player", "Player", "Player", 
	"Player", "Player", "Player", "Player", "Player"
};

enum Sprite
{
	SPRITE_PLAYER_LEFT = 0, SPRITE_PLAYER_RIGHT
};

// 화면 출력 함수
void Render()
{
	InitializeScreen();
	printf("Render\n");
	InitializeRender();
}

void UpdateRender()
{

}

void InitializeRender()
{
	printf("InitializeRender\n");
	InitializeSprites();
}

void InitializeSprites()
{
	Sprites = (Image**)malloc(sizeof(Image*) * SPRITES_COUNT);
	if (Sprites == NULL) { return; }
	for (int i = 0; i < SPRITES_COUNT; i++)
	{
		//Sprites[i] = LoadBitmapFile(SpriteName[i], COLOR_WHITE);
	}
	Sprites[0] = LoadBitmapFile("Player", COLOR_WHITE);
	RenderImage(0, 0, Sprites[0]);
}

void RenderImage(int x, int y, Image* image)
{
	printf("RenderImage\n");
	for (int posx = x; posx < x + image->width; posx++)
	{
		for (int posy = y; posy < y + image->height; posy++)
		{
			SetPixelColor(posx, posy, 0, image->bitmap[posx][posy]);
		}
	}
}