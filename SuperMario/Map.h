#pragma once
#include "Object.h"
typedef enum Tile { TILE_GROUND = 0, } Tile;

typedef char** TileData;
typedef char** TileTag;
typedef char** RoomData;

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