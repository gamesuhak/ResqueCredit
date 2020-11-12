#include "Map.h"
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"

extern const Coordination DIRECTIONS[DIRECTION_COUNT];
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


int CheckStageInvalidRoom()
{

}

// 해당 좌표의 대각선에 방이 있는지 확인
int CheckStageDiagonalRoom(Stage* stage, Coordination position)
{
	Coordination temp = position;
	if (stage->roomData[position.x - 1])
	{

	}
}

// 해당 좌표가 유효한지 확인
int CheckStageInvalidPosition()
{

}

void NewStage(Stage* stage)
{
	stage = (Stage*)malloc(sizeof(Stage));
	if (stage == NULL) { return NULL; }
	stage->id = 0;
	stage->roomData = NewArray(STAGE_SIZE, STAGE_SIZE);
	stage->width = STAGE_SIZE;
	stage->height = STAGE_SIZE;

	int roomMax = 10;
	int roomCount = 0;
	Coordination position =
	{
		Random(stage->width),
		Random(stage->height)
	};

	stage->roomData = 0;

	while (roomCount < roomMax - 1)
	{
		Bool createRoom = False;
		// 방이 생설될 때까지 반복
		while (createRoom == False)
		{
			// 방향 + 1로 만드는 이유는 탐색한 방향의 개수를 저장하기 위함
			int directionCheck[DIRECTION_COUNT + 1];
			for (int i = 0; i <= DIRECTION_COUNT; i++) { directionCheck[i] = 0; }
			// 랜덤으로 방향을 설정
			while (True)
			{
				int random = Random(DIRECTION_COUNT);
				// 4방향 전부 체크했을 때 반복문 탈출
				if (directionCheck[DIRECTION_COUNT] >= DIRECTION_COUNT) { break; }
				// 현재 방향을 이미 체크했을 때
				if (directionCheck[random] == 1) { continue; }

				Coordination temp = position;
				Coordination direction = DIRECTIONS[random];
				temp.x += direction.x;
				temp.y += direction.y;

				// 이동 불가능할 때
				if (temp.x < 0 || temp.y < 0 || temp.x >= stage->width - 1 || temp.y >= stage->height - 1)
				{
					continue;
				}
				// 방이 이미 있을 때
				if (stage->roomData[temp.x][temp.y] > ROOM_NOT)
				{
					continue;
				}

				if (temp.x > 1 && temp.x < stage->width + 1 && temp.y > 0 && temp.y < stage->height)
				{
					stage->roomData[temp.x - 1][temp.y] ;
				}
				break;
			}
			createRoom = True;
		}
		++roomCount;
	}

	

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
