#pragma once
#include "Object.h"
#define MAP_WIDTH			10
#define MAP_HEIGHT			10
#define LAYER_COUNT			1
typedef enum Tile { TILE_GROUND = 0, } Tile;

typedef char** TileData;
typedef char** TileTag;

typedef struct RoomInfo
{
	int variety;
	int width;
	int height;
	int percentage;
	TileData tile;
	TileTag tag;
	Creature** Monsters;
} RoomInfo;

typedef struct Room
{
	int id; // 고유숫자
	int variety; // 종류
	int width; // 가로길이
	int height; // 세로길이
	int monsterCount; // 몬스터 개체 수
	TileData tile; // 타일정보
	TileTag tag; // 타일태그
	Creature** monsters;
	Projectile** projectiles;
} Room;

typedef struct Map
{
	int id; // 고유숫자
	int width; // 가로길이
	int height; // 세로길이

	Creature** Monsters;
} Map;

void CreateStage();
Room* RandomRoom(int sumPercentage);
void LoadRoomInfos();
TileData NewTileData(int width, int height);