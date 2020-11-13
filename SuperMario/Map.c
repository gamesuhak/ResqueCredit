#include "Map.h"
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"
#include "Render.h"

extern const Coordination DIRECTIONS[DIRECTION_COUNT];
const int DOORS[DIRECTION_COUNT] = { 1, 2, 4, 8 };
Stage* Stage1 = NULL;
RoomInfo** RoomInfos = NULL;
int RoomInfoCount = 0;

Coordination PlayerRoom = { 0, 0 };

// ���������� �����ϰ� ���θ� ��ȯ�ϴ� �޼ҵ�
Bool InitializeStage()
{
	InitializeRoomInfo();
	for (int count = 0; count < LOOP_COUNT; count++)
	{
		Stage1 = NewStage(Stage1);
		
		if (Stage1 != NULL)
		{
			return True;
		}
	}
	printf("�� ���� �Ұ���");
	return False;
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

// door2�� ���� door1�� ��� ���� �����ϰ� ���� ��
// door1�� �ʿ��� ��, door2�� Ȯ���ϰ���� ��
Bool CheckDoor(int door1, int door2)
{
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		printf("%d, %d\n", (door1 & (1 << direction)), (door2 & (1 << direction)));
		// door1�� �ִ� ���� door2�� ���ٸ� �Ʒ� ���� -1�� ��
		if (((door1 & (1 << direction)) - (door2 & (1 << direction))) < 0)
		{
			return False;
		}
	}
	return True;
}

int CountDoor(int value)
{
	int count = 0;
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		if (value & (1 << direction))
		{
			++count;
		}
	}
	return count;
}

int CountNeighbor(Stage* stage, Coordination position)
{
	int count = 0;
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		Coordination temp = AddCoordination(position, DIRECTIONS[direction]);
		if (CheckStageValidPosition(stage, temp) && stage->roomData[temp.x][temp.y] > ROOM_NOT)
		{
			count = count | (1 << direction);
		}
	}
	return count;
}

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
						if (CountDoor(CountNeighbor(stage, ToCoordination(x, y))) == 1)
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
		RenderStage(0, 0, stage);
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
				Door neighborRoom = CountNeighbor(stage, ToCoordination(x, y)); // �ֺ��� �ʼ� ��
				for (int i = 0; i < roomCount; i++)
				{
					int id = RandomRoom(type);
					if (id < 0) { continue; }
					if (CheckDoor(neighborRoom, RoomInfos[id]->door))
					{
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
			printf("���� �����\n");
			Sleep(100);
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
	stage->rooms = (Room**)realloc(stage->rooms, sizeof(Room*) * stage->roomCount);
	if (stage->rooms == NULL) { return; }
	stage->rooms[++stage->roomCount - 1] = room;
}

// RoomInfos�� �ε����� �� ������ �Ķ���ͷ� ���� ������ �� ��ȯ�ϴ� �޼ҵ�
Room* NewRoom(int index, Door door)
{
	Room* room = (Room*)malloc(sizeof(Room));
	if (room == NULL) { return; }

	room->type = RoomInfos[index]->type;
	return room;
}

// �� ������ �ε����� �������� �������ִ� �޼ҵ�
int RandomRoom(RoomType type)
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

// �������� ���� �߰��ϴ� �޼ҵ�
void AddRoomInfo(Stage* stage, Room* room)
{
	RoomInfos = (Room**)realloc(RoomInfos, sizeof(Room*) * RoomInfoCount);
	if (stage->rooms == NULL) { return; }
	stage->rooms[++stage->roomCount - 1] = room;
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