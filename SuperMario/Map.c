#include "Map.h"
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"

Stage* Stage1 = NULL;
RoomInfo** RoomInfos = NULL;
int RoomInfoCount = 0;

Coordination PlayerRoom = { 0, 0 };

void InitializeMap()
{
	InitializeRoomInfo();
	NewStage(Stage1);
}

void InitializeRoomInfo()
{
	RoomInfos = (RoomInfo**)malloc(sizeof(RoomInfo*) * ROOMINFO_COUNT);
	if (RoomInfos == NULL) { return; }

	LoadRoomInfos();
}

void NewStage(Stage* stage)
{
	stage = (Stage*)malloc(sizeof(Stage));
	if (stage == NULL) { return NULL; }
	stage->id = 0;
	stage->roomData = NewArray(STAGE_SIZE, STAGE_SIZE);
	stage->width = STAGE_SIZE;
	stage->height = STAGE_SIZE;

	// 여기에 맵 틀 생성하는 부분 추가하기

	for (int y = 0; y < stage->height; y++)
	{
		for (int x = 0; x < stage->width; x++)
		{
			if (stage->roomData[x][y] < ROOM_START) { continue; }
			int type = stage->roomData[x][y];
			int id = RandomRoom(type);
			int door[4] = { 0, 0, 0, 0 };
			if (y > 0)
			{
				door[DIRECTION_UP] = stage->roomData[x][y - 1] > ROOM_NOT;
			}
			if (y < stage->height - 1)
			{
				door[DIRECTION_DOWN] = stage->roomData[x][y + 1] > ROOM_NOT;
			}
			if (x > 0)
			{
				door[DIRECTION_LEFT] = stage->roomData[x - 1][y] > ROOM_NOT;
			}
			if (x < stage->width - 1)
			{
				door[DIRECTION_RIGHT] = stage->roomData[x + 1][y] > ROOM_NOT;
			}

			stage->roomData[x][y] = NewRoom(id);
		}
	}
}

Room* NewRoom(int index)
{
	Room* room = (Room*)malloc(sizeof(Room));
	if (room == NULL) { return; }

	room->type = RoomInfos[index]->type;
	return room;
}

// 맵 정보의 인덱스를 랜덤으로 생성해주는 메소드
int RandomRoom(int type)
{
	int sumPercentage = 0; // 모든 방의 등장 퍼센테이지
	for (int i = 0; i < RoomInfoCount; i++) // 모든 방의 등장 퍼센테이지를 합산
	{
		if (RoomInfos[i]->type != type) { continue; }
		sumPercentage += RoomInfos[i]->percentage;
	}
	// 맵이 없으면 -1 반환
	if (sumPercentage == 0) { return -1; }

	// 0 ~ 퍼센테이지 - 1사이의 랜덤 값을 대입
	sumPercentage = Random(sumPercentage);
	for (int i = 0; i < RoomInfoCount; i++)
	{
		if (RoomInfos[i]->type != type) { continue; }
		if (RoomInfos[i]->percentage < sumPercentage)
		{
			return i;
		}
		sumPercentage -= RoomInfos[i]->percentage;
	}
	return -1;
}

void LoadRoomInfos()
{
	char name[ROOMINFO_COUNT] = "";
 	for (int i = 0; 1; i++)
	{
		sprintf(name, "%d", i);
		RoomInfo* roomInfo = LoadRoomFile(name);
		if (roomInfo == NULL) { return; }
		++RoomInfoCount;
		RoomInfos[i] = roomInfo;
	}
}
