#include "Stage.h"
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"

extern const Coordination DIRECTIONS[DIRECTION_COUNT]; // Object.c
extern RoomInfo** RoomInfos;

Stage* Stage1 = NULL; // �������� 1�� ������ ������ ������

// ���������� �����ϰ� ���θ� ��ȯ�ϴ� �޼ҵ�
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
	//printf("�� ���� �Ұ���");
	return False;
}

// ������������ ���� 4���� ���ļ� ���� ��츦 �����ϱ����� ����Ŭ�� üũ�ϴ� �޼ҵ�
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

// ���ο� ���������� �����ϴ� �޼ҵ�
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

	// ���������� ����� ������ �� ����
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

		// �������� ���� ��ġ�� �����ϴ� �κ�
		// ���� ���� ������ roomMax���� ������ �ݺ�
		while (roomCount < roomMax) //(True)
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
				if (stage->roomData[x][y] > ROOM_NOT)
				{
					if (stage->roomData[x][y] == DIRECTION_COUNT)
					{
						stage->roomData[x][y] = ROOM_START;
					}
					else
					{
						stage->roomData[x][y] = ROOM_MONSTER;
						// ���� �濡 �̿��� ���� 1�� �� ��
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
		// ������� ������ ���� ���� �̴��� ��
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
				Door neighborRoom = CountNeighbor(stage, NewCoordination(x, y)); // �ֺ��� �ʼ� ��
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

		// ������ �� ���� ä���� ���� ������ ���� ��
		if (roomCount > stage->roomCount)
		{
			//printf("���� ����� %d, %d\n",roomCount, stage->roomCount);
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

// ���������� ���� �߰��ϴ� �޼ҵ�
void AddRoom(Stage* stage, Room* room)
{
	stage->rooms = (Room**)realloc(stage->rooms, sizeof(Room*) * ++stage->roomCount);
	if (stage->rooms == NULL) { return; }
	stage->rooms[stage->roomCount - 1] = room;
}