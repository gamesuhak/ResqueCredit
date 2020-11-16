#pragma once
#include "Object.h"

#define ROOM_WIDTH			9
#define ROOM_HEIGHT			5

typedef enum RoomType { ROOM_NOT = -1, ROOM_START = 0, ROOM_BOSS, ROOM_MONSTER, ROOM_ITEM, ROOM_SECRET, ROOM_COUNT } RoomType;
typedef enum Tile { TILE_GROUND = 0 } Tile;
typedef enum TileTag { TILETAG_NONE = -1, TILETAG_WALL, TILETAG_DOOR } TileTag;

typedef char** TileData;
typedef char** CreatureData;
typedef int Door; // 문 정보, 비트별로 방향에 문이 있는지 데이터를 갖고 있다. 

typedef struct RoomInfo RoomInfo;
typedef struct Room Room;

struct RoomInfo
{
	int type;
	int width;
	int height;
	int percentage;
	TileData tile;
	TileData tag;
	Door door; // 문 정보
	int monsterCount;
	CreatureData monsters;
};

struct Room
{
	int id; // 고유숫자
	int type; // 종류
	int width; // 가로길이
	int height; // 세로길이
	int monsterCount; // 몬스터 개체 수
	TileData tile; // 타일정보
	TileData tag; // 타일태그
	Creature** monsters;
	Door door; // 문 정보
	Bool clear; // 방을 돌파했는지 여부
};

void InitializeRoomInfo();
RoomInfo* NewRoomInfo();
void AddRoomInfo(RoomInfo* room);

int RandomRoom(RoomType type);
Room* NewRoom(int index, Door door);

Bool CheckDoor(int door1, int door2);
int CountDoor(Door value);

void ProcessRoom();
void UpdateMonster(Room* room);
void UpdateProjectile(Room* room);
void CheckProjectile(Room* room, Projectile* projectile);

Coordination CheckMove(Room* room, Object* object, Coordination coordination);

TileTag GetTileTag(Room* room, Coordination coordination);