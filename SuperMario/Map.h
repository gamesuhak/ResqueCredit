#pragma once

#include "Object.h"
#define LOOP_COUNT			100
#define ROOM_WIDTH			9
#define ROOM_HEIGHT			5
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
typedef int Door; // 문 정보, 비트별로 방향에 문이 있는지 데이터를 갖고 있다. 

typedef struct RoomInfo RoomInfo;
typedef struct Room Room;
typedef struct Stage Stage;

struct RoomInfo
{
	int type;
	int width;
	int height;
	int percentage;
	TileData tile;
	TileTag tag;
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
	TileTag tag; // 타일태그
	Creature** monsters;
	Door door; // 문 정보
	Bool clear; // 방을 돌파했는지 여부
};

struct Stage
{
	int id; // 고유숫자
	int width;
	int height;
	RoomData roomData;
	Room** rooms;
	int roomCount;
	int roomInfo[ROOM_COUNT]; // 방이 몇개인지 확인하는
	Coordination start;
};

Bool InitializeStage();

Bool CheckStageLoop(Stage* stage, Coordination start, char direction, Coordination position);
Bool CheckStageValidRoom(Stage* stage, Coordination position);
Bool CheckStageValidPosition(Stage* stage, Coordination position);

int CountNeighbor(Stage* stage, Coordination position);
int CountDoor(int value);
Bool CheckDoor(int door1, int door2);



Stage* NewStage();
int RandomRoom(RoomType type);

void InitializeRoomInfo();
RoomInfo* NewRoomInfo();
void AddRoomInfo(Room* room);

void AddRoom(Stage* stage, Room* room);
Room* NewRoom(int index, Door door);

void ProcessObject();
void ProcessMonster(Room* room);
void ProcessProjectile(Room* room);
void CheckProjectile(Room* room, Projectile* projectile);
Coordination CheckMove(Room* room, int id, Object* object, Coordination direction);