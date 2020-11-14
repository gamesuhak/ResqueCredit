#include "Render.h"
//#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Sprite.h"
#include "Color.h"
#include "Animator.h"
#include "Bool.h"
#include "Map.h"

extern Stage* Stage1; // Map.c
extern Creature* Player; // Player.c
extern Room* PlayerRoom; // Player.c

extern Image** Sprites; // Sprite.c

extern Projectile** Projectiles; // Object.c
extern int ProjectileCount; // Object.c

Image* Screen; // 메인 화면 이미지
Image* Buffer; // 메인 화면 그리기 전에 그리는 구간

Image* CurrentRoom;
Image* Temp; // 트랜지션용 이미지
Bool IsTransition = False;

// 화면 출력 함수
void Render()
{
	InitializeScreen();
	InitializeSprites();
	InitializeRender();
	/*for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			RenderImage(PIXELPERUNIT * x, PIXELPERUNIT * y, Sprites[SPRITE_PLAYER + (y * 4) + x]);
			printf("%d==\n", SPRITE_PLAYER + (y * 4) + x);
		}
	}*/
	while (1)
	{
		//UpdateAnimation();
		UpdateRender();
	}
}

void StartTransition(Direction direction)
{
	IsTransition = True;
	DuplicateImage(CurrentRoom);
}

// Render를 초기화하는 함수
void InitializeRender()
{
	Screen = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);
	CurrentRoom = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT - PIXELPERUNIT);
}

// 화면을 갱신하는 함수
// 참고로 레이어별 / Y축 기준으로 정렬되어야됨
void UpdateRender()
{
	UpdateUI(Buffer); // UI 업데이트
	RenderRoom(PlayerRoom, CurrentRoom);
	AddImage(0, PIXELPERUNIT, CurrentRoom, Buffer);
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

void RenderRoom(Room* room, Image* target)
{
	AddImage(0, 0, Sprites[SPRITE_MAP], target);
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			//AddImage(x * PIXELPERUNIT, y * PIXELPERUNIT, Sprites[SPRITE_TILE + room->tile[x][y]], target);
		}
	}

	for (int layer = 0; layer < LAYER_COUNT; layer++)
	{
		AddImage(Player->object.position.x, Player->object.position.y, Sprites[Player->object.sprite], target);

		for (int i = 1; i < room->monsterCount; i++)
		{
			// 몬스터가 비활성화 돼있을 때 생략
			if (!room->monsters[i]->enable) { continue; }
			AddImage(room->monsters[i]->object.position.x, room->monsters[i]->object.position.y, Sprites[2], target);
		}
		for (int i = 0; i < ProjectileCount; i++)
		{
			// 투사체가 비활성화 돼있을 때 생략
			if (!Projectiles[i]->enable) { continue; }
			AddImage(Projectiles[i]->object.position.x, Projectiles[i]->object.position.y, Sprites[2], target);
		}
	}

	// 문을 출력하는 부분

	if (!room->clear)
	{

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
				SetPixelColor(posx + x, posy + y, COLOR_WHITE, stage->roomData[posx][posy] + 6);
			else
				SetPixelColor(posx + x, posy + y, COLOR_WHITE, COLOR_BLACK);
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
