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
	// ���� ������ ���� ���� ���� ��
	if (CompareCoordination(start, position))
	{
		return True;
	}

	// �ش� ��ǥ�� ��ȿ�� ��
	if (CheckStageValidPosition(stage, position))
	{
		// ���� ���� ������ �̵� ������ ��
		if (stage->roomData[position.x][position.y] > ROOM_NOT)
		{
			// ���� ���� ����� ��ȯ
			return CheckStageLoop(stage, start, direction, AddCoordination(position, DIRECTIONS[++direction % DIRECTION_COUNT]));
		}
	}
	return False;
}

// �ش� ��ǥ�� ���� �����ص� �Ǵ��� Ȯ��
Bool CheckStageValidRoom(Stage* stage, Coordination position)
{
	// �����¿�� 
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		if (CheckStageLoop(stage, position, direction, AddCoordination(position, DIRECTIONS[direction])))
		{
			return False;
		}
	}
	return True;
}

// �ش� ��ǥ�� ��ȿ���� Ȯ��
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

	// ���� ���� roomMax���� ������ �ݺ�
	while (roomCount < roomMax)
	{
		// ���� ���� ��ġ�� ������ ����, (-1, -1)�� �ʱ�ȭ
		char direction = DIRECTION_COUNT;
		// Ž���� ������ ���θ� �����ϴ� directionCheck
		// ���� + 1�� ����� ������ directionCheck[DIRECTION_COUNT]�� Ž���� ������ ������ �����ϱ� ����
		int directionCheck[DIRECTION_COUNT + 1];
		for (int i = 0; i <= DIRECTION_COUNT; i++) { directionCheck[i] = 0; }

		// �������� ������ ���� // 4���� ���� üũ���� �� �ݺ��� Ż��
		while (directionCheck[DIRECTION_COUNT] < DIRECTION_COUNT)
		{
			int random = Random(DIRECTION_COUNT);

			// ���� ������ �̹� üũ���� ��
			if (directionCheck[random] == 1) { continue; }

			// Ž���� ��ǥ�� temp�� ����
			Coordination temp = AddCoordination(position, DIRECTIONS[random]);

			// �̵� �����ϰ� ���� ���� ��
			if (CheckStageValidPosition(stage, temp) && stage->roomData[temp.x][temp.y] == ROOM_NOT)
			{
				// ���� ������ �� ���� ��
				if (CheckStageValidRoom(stage, temp))
				{
					// Ž���� ������ direction�� ����
					direction = random;
					break;
				}
			}

			directionCheck[random] = 1;
			++directionCheck[DIRECTION_COUNT];
		}
		// ���� ���� �� ���� ��
		if (direction == DIRECTION_COUNT)
		{
			// ���� ��ġ�� ���������̸� �� �̻��� ���� ���� �� ����
			if (stage->roomData[position.x][position.y] == DIRECTION_COUNT)
			{
				break;
			}
			else
			{
				// ���� ��ġ�� �̵��� �ݴ������ direction�� ����
				direction = (stage->roomData[position.x][position.y] + 2) % DIRECTION_COUNT;
				// direction�������� �̵�
				position = AddCoordination(position, DIRECTIONS[direction]);
			}
		}
		// ���� ���� �� ���� ��
		else
		{
			// direction�������� �̵�
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

// �� ������ �ε����� �������� �������ִ� �޼ҵ�
int RandomRoom(int type)
{
	int sumPercentage = 0; // ��� ���� ���� �ۼ�������
	for (int i = 0; i < RoomInfoCount; i++) // ��� ���� ���� �ۼ��������� �ջ�
	{
		if (RoomInfos[i]->type != type) { continue; }
		sumPercentage += RoomInfos[i]->percentage;
	}
	// ���� ������ -1 ��ȯ
	if (sumPercentage == 0) { return -1; }

	// 0 ~ �ۼ������� - 1������ ���� ���� ����
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
