#pragma once
#include "Object.h"
#define MAP_WIDTH		10
#define MAP_HEIGHT		10
#define LAYER_COUNT		3
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
	Coordination* MonstersPositions;
} RoomInfo;

typedef struct Room
{
	int id; // ��������
	int variety; // ����
	int width; // ���α���
	int height; // ���α���
	TileData tile; // Ÿ������
	TileTag tag; // Ÿ���±�
	Creature** Monsters;
} Room;

typedef struct Map
{
	int id; // ��������
	int width; // ���α���
	int height; // ���α���

	Creature** Monsters;
} Map;

void CreateStage();
Room* RandomRoom(int sumPercentage);
void LoadRoomInfos();
TileData NewTileData(int width, int height);