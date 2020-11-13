#pragma once
#include "Object.h"
#define LOOP_COUNT			100
#define MAP_WIDTH			10
#define MAP_HEIGHT			10
#define STAGE_SIZE			6
#define LAYER_COUNT			1
#define ROOMINFO_COUNT		5
typedef enum Tile { TILE_GROUND = 0 } Tile;
typedef enum RoomType { ROOM_NOT = -1, ROOM_START = 0, ROOM_BOSS, ROOM_MONSTER, ROOM_ITEM, ROOM_SECRET, ROOM_COUNT } RoomType;

typedef char** RoomData;
typedef char** TileData;
typedef char** TileTag;
typedef char** CreatureData;
typedef int Door; // �� ����, ��Ʈ���� ���⿡ ���� �ִ��� �����͸� ���� �ִ�. 

typedef struct RoomInfo
{
	int type;
	int width;
	int height;
	int percentage;
	TileData tile;
	TileTag tag;
	Door door; // �� ����
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
	Door door; // �� ����
	Bool clear; // ���� �����ߴ��� ����
} Room;

typedef struct Stage
{
	int id; // ��������
	int width;
	int height;
	RoomData roomData;
	Room** rooms;
	int roomCount;
	int roomInfo[ROOM_COUNT]; // ���� ����� Ȯ���ϴ�
} Stage;

Bool InitializeStage();
void InitializeRoomInfo();

Bool CheckStageLoop(Stage* stage, Coordination start, char direction, Coordination position);
Bool CheckStageValidRoom(Stage* stage, Coordination position);
Bool CheckStageValidPosition(Stage* stage, Coordination position);

int CountNeighbor(Stage* stage, Coordination position);
int CountDoor(int value);
Bool CheckDoor(int door1, int door2);

void AddRoom(Stage* stage, Room* room);
Room* NewRoom(int index, Door door);
Stage* NewStage();
int RandomRoom(int sumPercentage);
void LoadRoomInfos();