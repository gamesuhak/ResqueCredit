#include "Map.h"
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"

int RoomInfoCount;
RoomInfo** RoomInfos;
Room** Rooms;

void InitializeMap()
{
	LoadMapInfos();
	CreateStage();
}

void CreateStage()
{
	int stages[5][5] = { 0 };
	int sumPercentage = 0; // 모든 방의 등장 퍼센테이지

	// 모든 방의 등장 퍼센테이지를 합산
	for (int i = 0; i < RoomInfoCount; i++)
	{
		sumPercentage += RoomInfos[i]->percentage;
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			stages[j][i] = RandomRoom(sumPercentage);
		}
	}
}

Room* RandomRoom(int sumPercentage)
{
	for (int i = 0; i < RoomInfoCount; i++)
	{
		if (RoomInfos[i]->percentage < sumPercentage)
		{
			return RoomInfos[i];
		}
		sumPercentage -= RoomInfos[i]->percentage;
	}
	return NULL;
}

void LoadRoomInfos()
{
	RoomInfos[i] = 
}

TileData CreateMap(int width, int height)
{
	TileData tileData = (TileData)malloc(sizeof(char*) * width);
	if (tileData == NULL) { printf("CreateMap1\n"); return NULL; }
	tileData[0] = (char*)malloc(sizeof(char) * width * height);
	if (tileData[0] == NULL) { printf("CreateMap2\n"); return NULL; }
	for (int i = 1; i < width; i++)
	{
		tileData[i] = tileData[i - 1] + height;
		if (tileData[i] == NULL) { printf("CreateMap : %d\n", i); return NULL; }
	}
	memset(tileData[0], 0, sizeof(char) * width * height);
	return tileData;
}