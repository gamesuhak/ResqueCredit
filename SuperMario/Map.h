#pragma once
#include "Object.h"
#define MAP_WIDTH			10
#define MAP_HEIGHT			10
#define STAGE_SIZE			6
#define LAYER_COUNT			1
#define ROOMINFO_COUNT		5
typedef enum Tile { TILE_GROUND = 0, } Tile;

typedef char** MapData;
typedef char** TileData;
typedef char** TileTag;
typedef char** CreatureData;

typedef struct RoomInfo
{
	int variety;
	int width;
	int height;
	int percentage;
	TileData tile;
	TileTag tag;
	CreatureData** monsters;
} RoomInfo;

typedef struct Room
{
	int id; // ��������
	int variety; // ����
	int width; // ���α���
	int height; // ���α���
	int monsterCount; // ���� ��ü ��
	TileData tile; // Ÿ������
	TileTag tag; // Ÿ���±�
	Creature** monsters;
	Projectile** projectiles;
} Room;

typedef struct Map
{
	int id; // ��������
	int width;
	int height;
	//Room**
	MapData roomData;
} Map;

Room* NewRoom(int index);
void CreateStage(Map* map);
int RandomRoom(int sumPercentage);
void LoadRoomInfos();
TileData NewTileData(int width, int height);
TileData DuplicateData(TileData data, int width, int height);