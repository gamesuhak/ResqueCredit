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

// �ش� ��ǥ�� �밢���� ���� �ִ��� Ȯ��
int CheckStageDiagonalRoom(Stage* stage, Coordination position)
{
	Coordination temp = position;
	if (stage->roomData[position.x - 1])
	{

	}
}

// �ش� ��ǥ�� ��ȿ���� Ȯ��
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
		// ���� ������ ������ �ݺ�
		while (createRoom == False)
		{
			// ���� + 1�� ����� ������ Ž���� ������ ������ �����ϱ� ����
			int directionCheck[DIRECTION_COUNT + 1];
			for (int i = 0; i <= DIRECTION_COUNT; i++) { directionCheck[i] = 0; }
			// �������� ������ ����
			while (True)
			{
				int random = Random(DIRECTION_COUNT);
				// 4���� ���� üũ���� �� �ݺ��� Ż��
				if (directionCheck[DIRECTION_COUNT] >= DIRECTION_COUNT) { break; }
				// ���� ������ �̹� üũ���� ��
				if (directionCheck[random] == 1) { continue; }

				Coordination temp = position;
				Coordination direction = DIRECTIONS[random];
				temp.x += direction.x;
				temp.y += direction.y;

				// �̵� �Ұ����� ��
				if (temp.x < 0 || temp.y < 0 || temp.x >= stage->width - 1 || temp.y >= stage->height - 1)
				{
					continue;
				}
				// ���� �̹� ���� ��
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

	

	// ���⿡ �� Ʋ �����ϴ� �κ� �߰��ϱ�

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
