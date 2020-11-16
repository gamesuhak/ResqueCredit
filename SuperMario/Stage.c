#include "Stage.h"
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"

extern const Coordination DIRECTIONS[DIRECTION_COUNT]; // Object.c
extern RoomInfo** RoomInfos;

Stage* Stage1 = NULL; // 스테이지 1의 정보를 저장할 포인터

// 스테이지를 생성하고 여부를 반환하는 메소드
Bool InitializeStage()
{
	for (int count = 0; count < LOOP_COUNT; count++)
	{
		Stage1 = NewStage(Stage1);
		
		if (Stage1 != NULL)
		{
			return True;
		}
	}
	//printf("방 생성 불가능");
	return False;
}

// 스테이지에서 방이 4개가 겹쳐서 나올 경우를 방지하기위해 사이클을 체크하는 메소드
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

int CountNeighbor(Stage* stage, Coordination position)
{
	int count = 0;
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		Coordination temp = AddCoordination(position, DIRECTIONS[direction]);
		if (CheckStageValidPosition(stage, temp) && (stage->roomData[temp.x][temp.y] > ROOM_NOT))
		{
			count = count | (1 << direction);
		}
	}
	return count;
}

// 새로운 스테이지를 생성하는 메소드
Stage* NewStage()
{
	Stage* stage = (Stage*)malloc(sizeof(Stage));
	if (stage == NULL) { return NULL; }
	stage->id = 0;
	stage->width = STAGE_SIZE;
	stage->height = STAGE_SIZE;
	stage->roomData = NewArray(stage->width, stage->height);
	stage->rooms = NULL;
	stage->roomCount = 0;

	// 스테이지가 제대로 생성될 때 까지
	while (True)
	{
		for (int i = 0; i < ROOM_COUNT; i++)
		{
			stage->roomInfo[i] = 0;
		}
		SetArray(stage->roomData, stage->width, stage->height, ROOM_NOT);

		int roomMax = STAGE_SIZE * STAGE_SIZE * 0.4;
		int roomCount = 0;
		int bossRoom = 1;
		int itemRoom = 1;
		Coordination position =
		{
			Random(stage->width),
			Random(stage->height)
		};

		stage->start = position;
		stage->roomData[position.x][position.y] = DIRECTION_COUNT;

		// 랜덤으로 방의 위치를 생성하는 부분
		// 현재 방의 개수가 roomMax보다 작으면 반복
		while (roomCount < roomMax) //(True)
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
				if (stage->roomData[x][y] > ROOM_NOT)
				{
					if (stage->roomData[x][y] == DIRECTION_COUNT)
					{
						stage->roomData[x][y] = ROOM_START;
					}
					else
					{
						stage->roomData[x][y] = ROOM_MONSTER;
						// 현재 방에 이웃한 방이 1개 일 때
						if (CountDoor(CountNeighbor(stage, NewCoordination(x, y))) == 1)
						{
							if (bossRoom > 0)
							{
								stage->roomData[x][y] = ROOM_BOSS;
								--bossRoom;
							}
							else if (itemRoom > 0)
							{
								stage->roomData[x][y] = ROOM_ITEM;
								--itemRoom;
							}
						}
					}
				}
			}
		}
		// 보스방과 아이템 방이 기준 미달일 때
		if (bossRoom > 0 || itemRoom > 0)
		{
			continue;
		}
		
		stage->rooms = (Room**)malloc(sizeof(Room*) * roomCount);
		for (int y = 0; y < stage->height; y++)
		{
			for (int x = 0; x < stage->width; x++)
			{
				if (stage->roomData[x][y] == ROOM_NOT) { continue; }
				RoomType type = stage->roomData[x][y];
				Door neighborRoom = CountNeighbor(stage, NewCoordination(x, y)); // 주변의 필수 문
				for (int i = 0; i < roomCount; i++)
				{
					int id = RandomRoom(type);
					if (id < 0) { continue; }
					if (CheckDoor(neighborRoom, RoomInfos[id]->door))
					{
						//printf("%d\n", neighborRoom);
						Room* room = NewRoom(id, neighborRoom);
						AddRoom(stage, room);
						stage->roomData[x][y] = stage->roomCount - 1;
						break;
					}
				}
			}
		}

		// 생성된 방 보다 채워진 방의 개수가 작을 때
		if (roomCount > stage->roomCount)
		{
			//printf("방이 없어요 %d, %d\n",roomCount, stage->roomCount);
			for (int i = 0; i < stage->roomCount; i++)
			{
				free(stage->rooms[i]);
			}
			free(stage->rooms);
			stage->roomCount = 0;
			return NULL;
		}
		break;
	}
	return stage;
}

// 스테이지에 방을 추가하는 메소드
void AddRoom(Stage* stage, Room* room)
{
	stage->rooms = (Room**)realloc(stage->rooms, sizeof(Room*) * ++stage->roomCount);
	if (stage->rooms == NULL) { return; }
	stage->rooms[stage->roomCount - 1] = room;
}