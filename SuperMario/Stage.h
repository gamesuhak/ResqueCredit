#pragma once
#include "Room.h"

#define LOOP_COUNT			100
#define MAP_WIDTH			10
#define MAP_HEIGHT			10
#define STAGE_SIZE			6
#define LAYER_COUNT			1
//#define ROOMINFO_COUNT		5

typedef char** RoomData;

typedef struct Stage Stage;

struct Stage
{
	int id; // ��������
	int width;
	int height;
	RoomData roomData;
	Room** rooms;
	int roomCount;
	int roomInfo[ROOM_COUNT]; // ���� ����� Ȯ���ϴ�
	Coordination start;
};

Bool InitializeStage();

Stage* NewStage();

Bool CheckStageLoop(Stage* stage, Coordination start, char direction, Coordination position);
Bool CheckStageValidRoom(Stage* stage, Coordination position);
Bool CheckStageValidPosition(Stage* stage, Coordination position);

void AddRoom(Stage* stage, Room* room);

int CountNeighbor(Stage* stage, Coordination position);