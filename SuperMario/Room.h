#pragma once
#include "Object.h"

#define ROOM_WIDTH			9
#define ROOM_HEIGHT			5

typedef enum RoomType { ROOM_NOT = -1, ROOM_START = 0, ROOM_BOSS, ROOM_MONSTER, ROOM_ITEM, ROOM_SECRET, ROOM_COUNT } RoomType;
typedef enum Tile { TILE_GROUND = 0 } Tile;
typedef enum TileTag { TILETAG_NONE = -1, TILETAG_WALL, TILETAG_DOOR } TileTag;

typedef char** TileData;
typedef char** CreatureData;
typedef int Door; // �� ����, ��Ʈ���� ���⿡ ���� �ִ��� �����͸� ���� �ִ�. 

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
	Door door; // �� ����
	int monsterCount;
	CreatureData monsters;
};

struct Room
{
	int id; // ��������
	int type; // ����
	int width; // ���α���
	int height; // ���α���
	int monsterCount; // ���� ��ü ��
	TileData tile; // Ÿ������
	TileData tag; // Ÿ���±�
	Creature** monsters;
	Door door; // �� ����
	Bool clear; // ���� �����ߴ��� ����
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