#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Color.h"
#include "Animator.h"
#include "Bool.h"

// 게임 내에서 쓸 스프라이트 목록
Image** Sprites;
Image* Screen; // 메인 화면 이미지
Image* Buffer; // 메인 화면 그리기 전에 그리는 구간

//Image* CurrentRoom;
Image* BufferRoom;

extern int PlayerMapX;
extern int PlayerMapY;

extern Creature* Player;
extern Creature** Monsters;
extern Projectile** Projectiles;
extern int CreatureCount;
extern int ProjectileCount;

// 스프라이트의 이름들
const char* SPRITENAME[SPRITE_COUNT] = {
	"Map",

	// 플레이어 스프라이트, 12개나 있는 이유는 첫번째 이미지를 잘라 12개로 사용하기 때문에
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",

	"Monster",

	"UI", "UI", "UI",
};

// 화면 출력 함수
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

// Render를 초기화하는 함수
void InitializeRender()
{
	Screen = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);//NewArray(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);//NewArray(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// Sprites를 초기화하는 함수
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

// 화면을 갱신하는 함수
// 참고로 레이어별 / Y축 기준으로 정렬되어야됨
void UpdateRender()
{
	UpdateUI(Buffer); // UI 업데이트
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
			// 몬스터가 비활성화 돼있을 때 생략
			if (!Monsters[i]->enable) { continue; }

			AddImage(Monsters[i]->object.position.x, Monsters[i]->object.position.y, Sprites[2], target);
		}
		for (int i = 0; i < ProjectileCount; i++)
		{
			// 투사체가 비활성화 돼있을 때 생략
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

// UI를 그리는 메소드
void UpdateUI(Image* target)
{
	// 온전한 하트의 개수는 hp에서 1의 비트를 없앤 다음에 / 2한 결과
	int hpCount = (Player->hp ^ 1) >> 1;

	// 온전한 하트의 개수만큼 좌측 상단에서부터 우측으로 그림
	for (int i = 0; i < hpCount; i++)
	{
		AddImage(i * PIXELPERUNIT, 0, Sprites[SPRITE_HEART], target);
	}

	//HP가 홀수일 때
	if (Player->hp & 1)
	{
		AddImage((hpCount + 1) * PIXELPERUNIT, 0, Sprites[SPRITE_HEART_HALF], target);
	}
}

void UpdateAnimation()
{

}

// 스프라이트를 분할하여 Sprites에 저장하는 메소드 
// index 분할할 스프라이트의 번호, column
void ParseSprite(int index, int column, int row)
{
	Image** images = SliceImage(Sprites[index], column, row);
	for (int i = 0; i < column * row; i++)
	{
		Sprites[index + i] = images[i];
	}
	free(images);
}

// 일괄적으로 Sprite의 중심점을 수정하는 메소드
// index 스프라이트의 첫 번호, count = 일괄적으로 변경할 개수, pivot = 열거형 Pivot의 값
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