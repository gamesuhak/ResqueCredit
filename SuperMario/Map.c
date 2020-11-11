#include "Map.h"
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"

Map* Stage1 = NULL;
int RoomInfoCount = 0;
int PlayerRoom;
int PlayerRoomX;
int PlayerRoomY;

RoomInfo** RoomInfos = NULL;

void InitializeMap()
{
	RoomInfos = (RoomInfo**)malloc(sizeof(RoomInfo*) * RoomInfoCount);
	LoadRoomInfos();
	CreateStage(Stage1);
}

void CreateStage(Map* map)
{
	map = (Map*)malloc(sizeof(Map));
	if (map == NULL) { return NULL; }
	map->id = 0;
	map->roomData = NewTileData(STAGE_SIZE, STAGE_SIZE);
	map->width = STAGE_SIZE;
	map->height = STAGE_SIZE;

	int sumPercentage = 0; // 모든 방의 등장 퍼센테이지

	// 모든 방의 등장 퍼센테이지를 합산
	for (int i = 0; i < RoomInfoCount; i++)
	{
		sumPercentage += RoomInfos[i]->percentage;
	}

	int randomRoomNumber = 0;
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			// 랜덤으로 맵을 선택할 때 까지 반복
			do
			{
				randomRoomNumber = RandomRoom(sumPercentage);
			} while (map->roomData[j][i] < 1);
			map->roomData[j][i] = 
		}
	}
}

Room* NewRoom(int index)
{
	Room* room = (Room*)malloc(sizeof(Room));
	if (room == NULL) { return; }
	room->id = Stage1->

}

// 맵 정보의 인덱스를 랜덤으로 생성해주는 메소드
int RandomRoom(int sumPercentage)
{
	for (int i = 0; i < RoomInfoCount; i++)
	{
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
		roomInfo->variety = ++RoomInfoCount;
		RoomInfos[i] = roomInfo;
	}
}

TileData NewTileData(int width, int height)
{
	TileData tileData = NULL;
	tileData = (TileData)malloc(sizeof(char*) * width);
	if (tileData == NULL) { printf("CreateTileData2\n"); return NULL; }
	tileData[0] = (char*)malloc(sizeof(char) * width * height);
	if (tileData[0] == NULL) { printf("CreateTileData3\n"); return NULL; }
	for (int i = 1; i < width; i++)
	{
		tileData[i] = tileData[i - 1] + height;
		if (tileData[i] == NULL) { printf("CreateTileData : %d\n", i); return NULL; }
	}

	memset(tileData[0], 0, sizeof(char) * width * height);
	return tileData;
}

TileData DuplicateData(TileData data, int width, int height)
{
	TileData newData = NewTileData(width, height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			newData[x][y] = data[x][y];
		}
	}
	return newData;
}