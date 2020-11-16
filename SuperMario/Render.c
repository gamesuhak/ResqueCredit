#include "Render.h"
#include <stdio.h> // 

#include "Screen.h" // 
#include "FileLoader.h"
#include "Sprite.h"
#include "Color.h"
#include "Animator.h"
#include "Bool.h"
#include "Room.h"
#include "GameData.h"

extern SceneType Scene;
extern Stage* Stage1; // Stage.c
extern Creature* Player; // Player.c
extern Room* PlayerRoom; // Player.c
extern Bool PlayerFour;
extern Bool PlayerDouble;
extern Coordination PlayerRoomPosition;

extern Image** Sprites; // Sprite.c

extern Projectile** Projectiles; // Object.c
extern int ProjectileCount; // Object.c

Image* Screen; // 메인 화면 이미지
Image* Buffer; // 메인 화면 그리기 전에 그리는 구간

Image* CurrentRoom;
Image* Temp; // 트랜지션용 이미지
Image* UIBackGround; // UI 뒤에 그릴 검은 그림
Bool IsTransition = False;
extern const Coordination DIRECTIONS[DIRECTION_COUNT]; // Object.c

// 화면 출력 함수
void Render()
{
	while (1)
	{
		if (IsTransition)
		{
			continue;
		}
		if (Scene == SCENE_GAME)
		{
			RenderGame();
		}
		UpdateRender();
	}
}

void StartTransition(Direction direction)
{
	Coordination offset = DIRECTIONS[direction];
	Coordination zero = NewCoordination(0, 0);

	{
		int random = Random(5);
		switch (random)
		{
		case 0:
			Player->power++;
			break;
		case 1:
			Player->speed++;
			break;
		case 2:
			Player->cooltime--;
			if (Player->cooltime < 10)
			{
				Player->cooltime = 10;
			}
			break;
		case 3:
			PlayerFour = True;
			break;
		case 4:
			PlayerDouble = True;
			break;
		}
	}

	if (direction == DIRECTION_DOWN || direction == DIRECTION_UP)
	{
 		offset = MultiplyCoordination(offset, CurrentRoom->height);
	}
	else if (direction == DIRECTION_LEFT || direction == DIRECTION_RIGHT)
	{
		offset = MultiplyCoordination(offset, CurrentRoom->width);
	}
	IsTransition = True;
	Player->enable = False;
	if (Temp != NULL)
	{
		ReleaseImage(Temp);
	}
	Temp = DuplicateImage(CurrentRoom);
	
	RenderRoom(PlayerRoom, Temp);
	DisableProjectile(); // 발사체 초기화
	PlayerRoomPosition = AddCoordination(PlayerRoomPosition, DIRECTIONS[direction]);
	PlayerRoom = Stage1->rooms[Stage1->roomData[PlayerRoomPosition.x][PlayerRoomPosition.y]];
	if (PlayerRoom->type == ROOM_BOSS)
	{
		RenderImage(0, 0, Sprites[SPRITE_CLEAR]);
		exit(0);
	}
	Player->enable = True;
	if (direction == DIRECTION_DOWN)
	{
		Player->object.position = NewCoordination(5 * PIXELPERUNIT + 4, 1 * PIXELPERUNIT + 4);
	}
	if (direction == DIRECTION_UP)
	{
		Player->object.position = NewCoordination(5 * PIXELPERUNIT + 4, 5 * PIXELPERUNIT + 4);
	}
	if (direction == DIRECTION_LEFT)
	{
		Player->object.position = NewCoordination(9 * PIXELPERUNIT + 4, 3 * PIXELPERUNIT + 4);
	}
	if (direction == DIRECTION_RIGHT)
	{
		Player->object.position = NewCoordination(1 * PIXELPERUNIT + 4, 3 * PIXELPERUNIT + 4);
	}
	RenderRoom(PlayerRoom, CurrentRoom);

	direction = (direction + 2) % DIRECTION_COUNT;
	Coordination temp = NewCoordination(0, 0);
	while (!CompareCoordination(offset, zero))
	{
		AddImage(temp.x, temp.y + UI_HEIGHT, Temp, Buffer);
		AddImage(offset.x, offset.y + UI_HEIGHT, CurrentRoom, Buffer);
		offset = AddCoordination(offset, DIRECTIONS[direction]);
		temp = AddCoordination(temp, DIRECTIONS[direction]);
		UpdateUI(Buffer);
		UpdateRender();
		//Sleep(5);
	}
	IsTransition = False;
}

// Render를 초기화하는 함수
void InitializeRender()
{
	Screen = NewImage(SCREEN_WIDTH, SCREEN_HEIGHT);
	Buffer = NewImage(Screen->width, Screen->height);
	CurrentRoom = NewImage(Screen->width, Screen->height - UI_HEIGHT);
	UIBackGround = NewImage(UI_WIDTH, UI_HEIGHT);
	FillImage(UIBackGround, COLOR_BLACK);
}

void RenderGame()
{
	UpdateUI(Buffer); // UI 업데이트
	RenderRoom(PlayerRoom, CurrentRoom); // 방 그리기
	AddImage(0, UI_HEIGHT, CurrentRoom, Buffer);
}

// 화면을 갱신하는 함수
// 참고로 레이어별 / Y축 기준으로 정렬되어야됨
void UpdateRender()
{
	for (int posy = 0; posy < Screen->height; posy++)
	{
		for (int posx = 0; posx < Screen->width; posx++)
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
			if (room->tile[x][y] < 0)
			{
				continue;
			}
			AddImage(x * PIXELPERUNIT, y * PIXELPERUNIT, Sprites[SPRITE_TILE + room->tile[x][y]], target);
		}
	}

	// 문을 출력하는 부분

	if (room->door & (1 << DIRECTION_DOWN))
	{
		AddImage(4 * PIXELPERUNIT, 6 * PIXELPERUNIT, Sprites[SPRITE_TILE + 4], target);
		AddImage(5 * PIXELPERUNIT, 6 * PIXELPERUNIT, Sprites[SPRITE_TILE + 5], target);
		AddImage(6 * PIXELPERUNIT, 6 * PIXELPERUNIT, Sprites[SPRITE_TILE + 6], target);
	}
	if (room->door & (1 << DIRECTION_LEFT))
	{
		AddImage(0 * PIXELPERUNIT, 2 * PIXELPERUNIT, Sprites[SPRITE_TILE + 7], target);
		AddImage(0 * PIXELPERUNIT, 3 * PIXELPERUNIT, Sprites[SPRITE_TILE + 8], target);
		AddImage(0 * PIXELPERUNIT, 4 * PIXELPERUNIT, Sprites[SPRITE_TILE + 9], target);
	}
	if (room->door & (1 << DIRECTION_UP))
	{
		AddImage(4 * PIXELPERUNIT, 0 * PIXELPERUNIT, Sprites[SPRITE_TILE + 10], target);
		AddImage(5 * PIXELPERUNIT, 0 * PIXELPERUNIT, Sprites[SPRITE_TILE + 11], target);
		AddImage(6 * PIXELPERUNIT, 0 * PIXELPERUNIT, Sprites[SPRITE_TILE + 12], target);
	}
	if (room->door & (1 << DIRECTION_RIGHT))
	{
		AddImage(10 * PIXELPERUNIT, 2 * PIXELPERUNIT, Sprites[SPRITE_TILE + 13], target);
		AddImage(10 * PIXELPERUNIT, 3 * PIXELPERUNIT, Sprites[SPRITE_TILE + 14], target);
		AddImage(10 * PIXELPERUNIT, 4 * PIXELPERUNIT, Sprites[SPRITE_TILE + 15], target);
	}

	if (!room->clear)
	{
		if (room->door & (1 << DIRECTION_DOWN))
		{
			AddImage(5 * PIXELPERUNIT, 6 * PIXELPERUNIT, Sprites[SPRITE_TILE + DIRECTION_DOWN], target);
		}
		if (room->door & (1 << DIRECTION_UP))
		{
			AddImage(5 * PIXELPERUNIT, 0 * PIXELPERUNIT, Sprites[SPRITE_TILE + DIRECTION_UP], target);
		}
		if (room->door & (1 << DIRECTION_LEFT))
		{
			AddImage(0 * PIXELPERUNIT, 3 * PIXELPERUNIT, Sprites[SPRITE_TILE + DIRECTION_LEFT], target);
		}
		if (room->door & (1 << DIRECTION_RIGHT))
		{
			AddImage(10 * PIXELPERUNIT, 3 * PIXELPERUNIT, Sprites[SPRITE_TILE + DIRECTION_RIGHT], target);
		}
	}

	for (int layer = 0; layer < LAYER_COUNT; layer++)
	{
		if (Player->enable)
		{
			AddImage(Player->object.position.x, Player->object.position.y, Sprites[Player->object.sprite], target);
		}
		
		for (int i = 0; i < room->monsterCount; i++)
		{
			// 몬스터가 비활성화 돼있을 때 생략
			if (!room->monsters[i]->enable) { continue; }
			AddImage(room->monsters[i]->object.position.x, room->monsters[i]->object.position.y, Sprites[room->monsters[i]->object.sprite], target);
		}
		for (int i = 0; i < ProjectileCount; i++)
		{
			// 투사체가 비활성화 돼있을 때 생략
			if (!Projectiles[i]->enable) { continue; }
			AddImage(Projectiles[i]->object.position.x, Projectiles[i]->object.position.y, Sprites[Projectiles[i]->object.sprite], target);
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
				SetPixelColor(posx + x, posy + y, COLOR_WHITE, stage->roomData[posx][posy] + 6);
			else
				SetPixelColor(posx + x, posy + y, COLOR_WHITE, COLOR_BLACK);
		}
	}
}

// UI를 그리는 메소드
void UpdateUI(Image* target)
{
	if (Player->hp <= 0)
	{
		RenderImage(0, 0, Sprites[SPRITE_GAMEOVER]);
		exit(0);
	}
	AddImage(UI_X, UI_Y, UIBackGround, target);
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
		AddImage((hpCount) * PIXELPERUNIT, 0, Sprites[SPRITE_HEART_HALF], target);
	}
}

void UpdateAnimation()
{

}
