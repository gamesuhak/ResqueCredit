#include "Map.h"
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"
#include "Render.h"

extern const Coordination DIRECTIONS[DIRECTION_COUNT];
Stage* Stage1 = NULL;
RoomInfo** RoomInfos = NULL;
int RoomInfoCount = 0;

Coordination PlayerRoom = { 0, 0 };

void InitializeStage()
{
	InitializeRoomInfo();
	Stage1 = NewStage(Stage1);
}

void PrintStage(Stage* stage)
{
	system("cls");
	for (int y = 0; y < stage->height; y++)
	{
		for (int x = 0; x < stage->width; x++)
		{
			if (stage->roomData[x][y] == ROOM_NOT)
			{
				printf("-");
			}
			else
			{
				printf("%d", stage->roomData[x][y]);
			}

		}
		printf("\n");
	}
}

void InitializeRoomInfo()
{
	RoomInfos = (RoomInfo**)malloc(sizeof(RoomInfo*) * ROOMINFO_COUNT);
	if (RoomInfos == NULL) { return; }

	LoadRoomInfos();
}

Bool CheckStageLoop(Stage* stage, Coordination start, char direction, Coordination position)
{
	// 시작 지점과 현재 방이 같을 때
	if (CompareCoordination(start, position))
	{
		return True;
	}

	// 해당 좌표가 유효할 때
	if (CheckStageValidPosition(stage, position))
	{
		// 만약 다음 방으로 이동 가능할 때
		if (stage->roomData[position.x][position.y] > ROOM_NOT)
		{
			// 다음 방의 결과를 반환
			return CheckStageLoop(stage, start, direction, AddCoordination(position, DIRECTIONS[++direction % DIRECTION_COUNT]));
		}
	}
	return False;
}

// 해당 좌표에 방을 생성해도 되는지 확인
Bool CheckStageValidRoom(Stage* stage, Coordination position)
{
	// 상하좌우로 
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		if (CheckStageLoop(stage, position, direction, AddCoordination(position, DIRECTIONS[direction])))
		{
			return False;
		}
	}
	return True;
}

// 해당 좌표가 유효한지 확인
Bool CheckStageValidPosition(Stage* stage, Coordination position)
{
	if (position.x >= 0 && position.x < stage->width && position.y >= 0 && position.y < stage->height)
	{
		return True;
	}
	return False;
}

Stage* NewStage()
{
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	if (stage == NULL) { return NULL; }
	stage->id = 0;
	stage->roomData = NewArray(STAGE_SIZE, STAGE_SIZE);
	stage->width = STAGE_SIZE;
	stage->height = STAGE_SIZE;
	SetArray(stage->roomData, stage->width, stage->height, ROOM_NOT);

	int roomMax = 10;
	int roomCount = 0;
	Coordination position =
	{
		Random(stage->width),
		Random(stage->height)
	};

	stage->roomData[position.x][position.y] = DIRECTION_COUNT;

	// 현재 방이 roomMax보다 작으면 반복
	while (roomCount < roomMax)
	{
		// 방을 만들 위치를 저장할 변수, (-1, -1)로 초기화
		char direction = DIRECTION_COUNT;
		// 탐색한 방향의 여부를 저장하는 directionCheck
		// 방향 + 1로 만드는 이유는 directionCheck[DIRECTION_COUNT]에 탐색한 방향의 개수를 저장하기 위함
		int directionCheck[DIRECTION_COUNT + 1];
		for (int i = 0; i <= DIRECTION_COUNT; i++) { directionCheck[i] = 0; }

		// 랜덤으로 방향을 설정 // 4방향 전부 체크했을 때 반복문 탈출
		while (directionCheck[DIRECTION_COUNT] < DIRECTION_COUNT)
		{
			int random = Random(DIRECTION_COUNT);

			// 현재 방향을 이미 체크했을 때
			if (directionCheck[random] == 1) { continue; }

			// 탐색용 좌표를 temp에 대입
			Coordination temp = AddCoordination(position, DIRECTIONS[random]);

			// 이동 가능하고 방이 없을 때
			if (CheckStageValidPosition(stage, temp) && stage->roomData[temp.x][temp.y] == ROOM_NOT)
			{
				// 방을 생성할 수 있을 때
				if (CheckStageValidRoom(stage, temp))
				{
					// 탐색한 방향을 direction에 저장
					direction = random;
					break;
				}
			}

			directionCheck[random] = 1;
			++directionCheck[DIRECTION_COUNT];
		}
		// 방을 만들 수 없을 때
		if (direction == DIRECTION_COUNT)
		{
			// 현재 위치가 시작지점이면 더 이상은 방을 만들 수 없음
			if (stage->roomData[position.x][position.y] == DIRECTION_COUNT)
			{
				break;
			}
			else
			{
				// 현재 위치로 이동한 반대방향을 direction에 대입
				direction = (stage->roomData[position.x][position.y] + 2) % DIRECTION_COUNT;
				// direction방향으로 이동
				position = AddCoordination(position, DIRECTIONS[direction]);
			}
		}
		// 방을 만들 수 있을 때
		else
		{
			// direction방향으로 이동
			position = AddCoordination(position, DIRECTIONS[direction]);
			stage->roomData[position.x][position.y] = direction;
			++roomCount;
		}
	}

	for (int y = 0; y < stage->height; y++)
	{
		for (int x = 0; x < stage->width; x++)
		{
			if (stage->roomData[x][y] == ROOM_NOT) { continue; }
			int type = stage->roomData[x][y];
			int id = RandomRoom(type);
			int door[DIRECTION_COUNT] = { 0, 0, 0, 0 };
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

			//stage->roomData[x][y] = NewRoom(id);
		}
	}
	return stage;
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
