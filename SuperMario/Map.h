#pragma once
#include "Object.h"
#define MAP_WIDTH			10
#define MAP_HEIGHT			10
#define STAGE_SIZE			6
#define LAYER_COUNT			1
#define ROOMINFO_COUNT		5
typedef enum Tile { TILE_GROUND = 0 } Tile;
typedef enum RoomType { ROOM_NOT, ROOM_START = 0, ROOM_BOSS, ROOM_MONSTER, ROOM_ITEM, ROOM_SECRET, ROOM_COUNT } RoomType;

typedef char** MapData;
typedef char** TileData;
typedef char** TileTag;
typedef char** CreatureData;

typedef struct RoomInfo
{
	int type;
	int width;
	int height;
	int percentage;
	TileData tile;
	TileTag tag;
	CreatureData** monsters;
} RoomInfo;

typedef struct Room
{
	int id; // 고유숫자
	int type; // 종류
	int width; // 가로길이
	int height; // 세로길이
	int monsterCount; // 몬스터 개체 수
	TileData tile; // 타일정보
	TileTag tag; // 타일태그
	Creature** monsters;
	Projectile** projectiles;
} Room;

typedef struct Stage
{
	int id; // 고유숫자
	int width;
	int height;
	//Room**
	MapData roomData;
} Stage;

void InitializeMap();
void InitializeRoomInfo();

Room* NewRoom(int index);
void NewStage(Stage* stage);
int RandomRoom(int sumPercentage);
void LoadRoomInfos();