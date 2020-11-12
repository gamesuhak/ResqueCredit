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
	int id; // ��������
	int type; // ����
	int width; // ���α���
	int height; // ���α���
	int monsterCount; // ���� ��ü ��
	TileData tile; // Ÿ������
	TileTag tag; // Ÿ���±�
	Creature** monsters;
	Projectile** projectiles;
} Room;

typedef struct Stage
{
	int id; // ��������
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