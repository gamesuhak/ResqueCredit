#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Color.h"
#include "Object.h"
#include "Map.h"
#include "Animator.h"
#include "Bool.h"

// 게임 내에서 쓸 스프라이트 목록
Image** Sprites;
Bitmap Screen; // 메인 화면 이미지
Bitmap Buffer; // 메인 화면 그리기 전에 그리는 구간

Bitmap CurrentRoom;
Bitmap BuferRoom;

extern int PlayerMapX;
extern int PlayerMapY;

bool IsTransition = false;
int TransitionX;
int TransitionY;

extern Creature* Player;
extern Creature** Monsters;
extern Projectile** Projectiles;
extern int CreatureCount;
extern int ProjectileCount;

// 스프라이트의 이름들
const char* SPRITENAME[SPRITES_COUNT] = {
	"Map",
	"FinnDown0", "FinnDown1", "FinnDown2",
	"FinnUp0", "FinnUp1", "FinnUp2",
	"FinnLeft0", "FinnLeft1", "FinnLeft2",
	"FinnRight0", "FinnRight1", "FinnRight2",
	"Monster",

	"UI_Heart",
	"UI_Heart_Half",
	"UI_Heart",
};

// 화면 출력 함수
void Render()
{
	InitializeScreen();
	InitializeRender();
	InitializeSprites();
	while (1)
	{
		
		if (IsTransition)
		{

		}
		else
		{
			UpdateAnimation();
			UpdateRender();
		}
		
	}
}

// 화면을 갱신하는 함수
// 참고로 레이어별 / Y축 기준으로 정렬되어야됨
void UpdateRender()
{
	if (IsTransition)
	{

	}

	UpdateUI(); // UI 업데이트
	RenderCamera();

	
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

void RenderMap(Room* room, Bitmap target)
{
	for (int layer; layer < LAYER_COUNT; layer++)
	{
		AddImage(0, 0, Sprites[0], Buffer);
		AddImage(Player->object.position.x, Player->object.position.y, Sprites[1], Buffer);
		for (int i = 1; i < CreatureCount; i++)
		{
			// 몬스터가 비활성화 돼있을 때 생략
			if (!Monsters[i]->enable) { continue; }

			AddImage(Monsters[i]->object.position.x, Monsters[i]->object.position.y, Sprites[2], Buffer);
		}
		for (int i = 0; i < ProjectileCount; i++)
		{
			// 투사체가 비활성화 돼있을 때 생략
			if (!Projectiles[i]->enable) { continue; }

			AddImage(Projectiles[i]->object.position.x, Projectiles[i]->object.position.y, Sprites[2], Buffer);
		}
	}



	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			room->tile[x][y]
		}
	}
}

// Render를 초기화하는 함수
void InitializeRender()
{
	Screen = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewBitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Sprites를 초기화하는 함수
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

	Sprites[SPRITE_HEART] = LoadBitmapFile(SPRITENAME[SPRITE_MONSTER], COLOR_BLACK);
	//RenderImage(0, 0, Sprites[1]);
}

void UpdateUI()
{
	for (int i = 0; i <	Player->hp; i++)
	{
		//HP가 홀수일 때
		if (i ^ 1 == 1)
		{
			AddImage(SCREEN_WIDTH - (i >> 1) * 16, 0, Sprites[SPRITE_HEART], Buffer);
		}
		else
		{
			AddImage(SCREEN_WIDTH - (i >> 1) * 16, 0, Sprites[SPRITE_HEART], Buffer);
		}
	}
}

// 이미지를 화면에 그리는 함수 나중에 처분할 예정
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

// 이미지를 이미지에 그리는 함수
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

// 이미지를 이미지에 그리는 함수
void AddImage2(int x, int y, Image* image, Image* target)
{
	for (int posx = 0; posx < image->width; posx++)
	{
		for (int posy = 0; posy < image->height; posy++)
		{
			if ((image->bitmap[posx][posy] < 0) || ((posx + x - image->pivotx < 0) || (posy + y - image->pivoty < 0)))
			{
				continue;
			}
			target->bitmap[posx + x - image->pivotx][posy + y - image->pivoty] = image->bitmap[posx][posy];
		}
	}
}

void UpdateAnimation()
{

}

void RenderCamera()
{
	for (int y = 0; y < )
	{
		for (int x = 0; x < )
		{

		}
	}
}