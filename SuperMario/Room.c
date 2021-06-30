#include "Room.h"

#include <stdio.h>
#include "Sprite.h" // PIXELPERUNIT
#include "FileLoader.h" // LoadRoomInfoFile
#include "Function.h"
#include "Sound.h"
#include "GameData.h"

extern SceneType Scene;
extern Bool IsTransition; // Render.c
extern Bool Pause; // Main.c

extern const Coordination DIRECTIONS[DIRECTION_COUNT]; // Object.c
extern Projectile** Projectiles; // Object.c
extern int ProjectileCount; // Object.c

extern Creature* Player; // Player.c
extern Room* PlayerRoom; // Player.c


const int DOORS[DIRECTION_COUNT] = { 1, 2, 4, 8 };

RoomInfo** RoomInfos = NULL; // 방 정보를 저장할 2차원 포인터
int RoomInfoCount = 0; // 방 정보의 개수를 저장할 변수

void InitializeRoomInfo()
{
	/*RoomInfo* room = NewRoomInfo();
	SetArray(room->monsters, ROOM_WIDTH, ROOM_HEIGHT, -1);
	room->monsters[1][1] = 0;
	room->monsters[ROOM_WIDTH - 2][1] = 0;
	room->monsters[ROOM_WIDTH - 2][ROOM_HEIGHT - 2] = 0;
	SaveRoomInfoFile("002", room);
	exit(0);*/
	RoomInfos = (RoomInfo**)malloc(sizeof(RoomInfo*));
	if (RoomInfos == NULL) { return; }

	char name[10] = "";
	for (int i = 0; 1; i++)
	{
		sprintf(name, "%03d", i);
		RoomInfo* roomInfo = LoadRoomInfoFile(name);
		if (roomInfo == NULL) { return; }
		++RoomInfoCount;
		AddRoomInfo(roomInfo);
	}
}



// 초기화된 방 정보를 생성
RoomInfo* NewRoomInfo()
{
	RoomInfo* room = (RoomInfo*)malloc(sizeof(RoomInfo));
	if (room == NULL) { return; }
	room->type = ROOM_START;
	room->width = ROOM_WIDTH;
	room->height = ROOM_HEIGHT;
	room->percentage = 10;
	room->tile = NewArray(room->width, room->height);
	room->tag = NewArray(room->width, room->height);
	room->monsterCount = 0;
	room->monsters = NewArray(room->width, room->height);
	room->door = 0;
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		room->door = room->door | (1 << direction);
	}
	return room;
}

// 방정보에 방을 추가하는 메소드
void AddRoomInfo(RoomInfo* room)
{
	if (RoomInfos == NULL) { return; }
	RoomInfos = (RoomInfo**)realloc(RoomInfos, sizeof(RoomInfo*) * RoomInfoCount);
	if (RoomInfos == NULL) { return; }
	RoomInfos[RoomInfoCount - 1] = room;
}

// 맵 정보의 인덱스를 랜덤으로 생성해주는 메소드
int RandomRoom(RoomType type)
{
	int sumPercentage = 0; // 모든 방의 등장 퍼센테이지
	for (int i = 0; i < RoomInfoCount; i++) // 모든 방의 등장 퍼센테이지를 합산
	{
		if (RoomInfos[i]->type != type) { continue; }
		sumPercentage += RoomInfos[i]->percentage;
	}
	// 맵이 없으면 -1 반환
	if (sumPercentage == 0) { return -1; }

	// 0 ~ 퍼센테이지 - 1사이의 랜덤 값을 대입
	sumPercentage = Random(sumPercentage);
	for (int i = 0; i < RoomInfoCount; i++)
	{
		if (RoomInfos[i]->type != type) { continue; }
		if (sumPercentage < RoomInfos[i]->percentage)
		{
			return i;
		}
		sumPercentage -= RoomInfos[i]->percentage;
	}
	return -1;
}

// RoomInfos의 인덱스와 문 정보를 파라미터로 방을 생성한 뒤 반환하는 메소드
Room* NewRoom(int index, Door door)
{
	Room* room = (Room*)malloc(sizeof(Room));
	if (room == NULL) { return NULL; }

	room->type = RoomInfos[index]->type;
	room->width = RoomInfos[index]->width;
	room->height = RoomInfos[index]->height;
	room->door = door;
	room->tile = DuplicateArray(RoomInfos[index]->tile, room->width, room->height);
	room->tag = DuplicateArray(RoomInfos[index]->tag, room->width, room->height);
	room->monsterCount = 0;
	
	room->monsters = (Creature**)malloc(sizeof(Creature*));
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			//printf("%02d", RoomInfos[index]->monsters[x][y]);
			if (x == 0 || x == ROOM_WIDTH - 1 || y == 0 || y == ROOM_HEIGHT - 1)
			{
				room->tag[x][y] = TILETAG_WALL;
			}
			int id;
			if ((id = RoomInfos[index]->monsters[x][y]) < 0) // 여기서 오류떴음
			{
				continue;
			}
			room->monsters = (Creature**)realloc(room->monsters, sizeof(Creature*) * ++room->monsterCount);
			if (room->monsters == NULL) { printf("Monster할당오류"); exit(1); }
			Creature* monster = NewMonster(id);
			monster->object.position.x = x * PIXELPERUNIT + monster->object.collider.pivot.x;
			monster->object.position.y = y * PIXELPERUNIT + monster->object.collider.pivot.y;
			monster->enable = True;
			room->monsters[room->monsterCount - 1] = monster;
			
		}
	}
	room->clear = room->monsterCount == 0;
	if (door & 1 << DIRECTION_DOWN)
	{
		room->tag[5][ROOM_HEIGHT - 1] = TILETAG_DOOR;
	}
	if (door & 1 << DIRECTION_LEFT)
	{
		room->tag[0][3] = TILETAG_DOOR;
	}
	if (door & 1 << DIRECTION_RIGHT)
	{
		room->tag[ROOM_WIDTH - 1][3] = TILETAG_DOOR;
	}
	if (door & 1 << DIRECTION_UP)
	{
		room->tag[5][0] = TILETAG_DOOR;
	}

	return room;
}

// Door 값을 int로 변환하는 메소드
int CountDoor(Door value)
{
	int count = 0;
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		if (value & (1 << direction))
		{
			++count;
		}
	}
	return count;
}

// door2의 문이 door1의 모든 문을 포함하고 있을 때
// door1이 필요한 문, door2가 확인하고싶은 문
Bool CheckDoor(int door1, int door2)
{
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		// door1에 있는 문이 door2에 없을 때
		if ((door1 & (1 << direction)) > (door2 & (1 << direction)))
		{
			return False;
		}
	}
	return True;
}

// 방에서 이루어지는 처리과정
void ProcessRoom()
{
	InitializeObject();

	while (1)
	{
		if (Pause) { continue; }
		if (IsTransition | (Scene == SCENE_GAMEOVER) | (Scene == SCENE_CLEAR))
		{
			continue;
		}
		UpdateAnimator(&Player->object);
		UpdateMonster(PlayerRoom);
		UpdateProjectile(PlayerRoom);
		Sleep(20);
		if (!PlayerRoom->clear)
		{
			PlayerRoom->clear = IsRoomClear(PlayerRoom);
		}
	}
}

Bool IsRoomClear(Room* room)
{
	for (int i = 0; i < room->monsterCount; i++)
	{
		if (room->monsters[i]->enable)
		{
			return False;
		}
	}
	return True;
}

void UpdateMonster(Room* room)
{
	for (int i = 0; i < room->monsterCount; i++)
	{
		if (room->monsters[i]->enable)
		{
			room->monsters[i]->object.direction = Random(DIRECTION_COUNT);
			Coordination direction = DIRECTIONS[room->monsters[i]->object.direction];
			direction = MultiplyCoordination(direction, room->monsters[i]->speed);
			direction = CheckMove(room, &(room->monsters[i]->object), direction);
			room->monsters[i]->object.position = AddCoordination(room->monsters[i]->object.position, direction);
			UpdateAnimator(&room->monsters[i]->object);
			if (++room->monsters[i]->cooltime > 50)
			{
				room->monsters[i]->cooltime = 0;
				PlayFMODSound(SOUND_ARROW);
				ShootProjectile(1, room->monsters[i]->object.position, room->monsters[i]->object.direction, room->monsters[i]->projectile, room->monsters[i]->power, 1);

			}
		}
	}
}

void UpdateProjectile(Room* room)
{
	for (int i = 0; i < ProjectileCount; i++)
	{
		if (Projectiles[i]->enable == True)
		{
			Coordination temp = DIRECTIONS[Projectiles[i]->object.direction];
			temp = MultiplyCoordination(temp, Projectiles[i]->speed);
			Projectiles[i]->object.position = AddCoordination(Projectiles[i]->object.position, temp);
			CheckProjectile(room, Projectiles[i]);
			if (--Projectiles[i]->distance == 0)
			{
				Projectiles[i]->enable = False;
			}
			UpdateAnimator(&Projectiles[i]->object);
		}
	}
}

//Coordination CheckMove(Room* room, int id, Object* object, Coordination coordination)
Coordination CheckMove(Room* room, Object* object, Coordination coordination)
{
	Coordination temp = { 0, 0 };

	if (object != &Player->object)
	{
		temp.x = coordination.x;
		temp.y = 0;
		if (CheckCollider(object, &Player->object, temp))
		{
			coordination.x = 0;
		}
		temp.x = 0;
		temp.y = coordination.y;
		if (CheckCollider(object, &Player->object, temp))
		{
			coordination.y = 0;
		}
	}

	// 방에 존재하는 몬스터의 수 만큼 반복
	for (int i = 0; i < room->monsterCount; i++)
	{
		// 몬스터의 id가 자신이거나 비활성화 돼있을 때 스킵
		//if (room->monsters[i]->id == id || !room->monsters[i]->enable || (object->layer != room->monsters[i]->object.layer))
		// 몬스터가 자신이거나 비활성화 되어있거나 레이어가 다를 때 건너 뜀
		if (&room->monsters[i]->object == object || !room->monsters[i]->enable || (object->layer != room->monsters[i]->object.layer))
		{
			continue;
		}
		temp.x = coordination.x;
		temp.y = 0;
		if (CheckCollider(object, &(room->monsters[i]->object), temp))
		{
			coordination.x = 0;
		}
		temp.x = 0;
		temp.y = coordination.y;
		if (CheckCollider(object, &(room->monsters[i]->object), temp))
		{
			coordination.y = 0;
		}
	}

	temp.x = coordination.x;
	temp.y = 0;

	TileTag tag = GetTileTag(room, AddCoordination(object->position, temp));
	if (tag == TILETAG_WALL || (tag == TILETAG_DOOR && !room->clear))
	{ 
		coordination.x = 0;
	}

	temp.x = 0;
	temp.y = coordination.y;
	tag = GetTileTag(room, AddCoordination(object->position, temp));
	if (tag == TILETAG_WALL || (tag == TILETAG_DOOR && !room->clear)) 
	{
		coordination.y = 0;
	}

	return coordination;
}

// 좌표에 있는 타일태그를 반환
TileTag GetTileTag(Room* room, Coordination coordination)
{
	coordination = DivideCoordination(coordination, PIXELPERUNIT);
	return room->tag[coordination.x][coordination.y];
}

// 활성화 된 몬스터의 개수를 반환
int CountMonster(Room* room)
{
	int count = 0;
	for (int i = 0; i < room->monsterCount; i++)
	{
		if (room->monsters[i]->enable)
		{
			++count;
		}
	}
	return count;
}

void CheckProjectile(Room* room, Projectile* projectile)
{
	Coordination zero = NewCoordination(0, 0);
	if (projectile->from == 1)
	{
		if (CheckCollider(&projectile->object, &Player->object, zero) == True)
		{
			PlayFMODSound(SOUND_HIT);
			HitProjectile(projectile, Player);
		}
		return;
	}
	for (int i = 0; i < room->monsterCount; i++)
	{
		if (room->monsters[i]->enable == True)
		{
			if (CheckCollider(&projectile->object, &room->monsters[i]->object, zero) == True)
			{
				HitProjectile(projectile, room->monsters[i]);
				PlayFMODSound(SOUND_HIT);
			}
		}
	}
	TileTag tag = GetTileTag(room, projectile->object.position);
	if (tag == TILETAG_WALL || tag == TILETAG_DOOR)
	{
		projectile->enable = False;
	}
}