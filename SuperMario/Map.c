#include "Map.h"
#include <stdio.h>
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc
#include "Function.h"
#include "Render.h"
#include "FileLoader.h" // LoadRoomInfoFile

extern const Coordination DIRECTIONS[DIRECTION_COUNT];
const int DOORS[DIRECTION_COUNT] = { 1, 2, 4, 8 };

extern Projectile** Projectiles;
extern int ProjectileCount;

Stage* Stage1 = NULL;
RoomInfo** RoomInfos = NULL;
int RoomInfoCount = 0;

// 스테이지를 생성하고 여부를 반환하는 메소드
Bool InitializeStage()
{
	InitializeRoomInfo();
	printf("입력된 파일 개수 : %d\n", RoomInfoCount);
	for (int i = 0; i < RoomInfoCount; i++)
	{
		printf("%d의 타입 : %d\n", i, RoomInfos[i]->type);
	}

	for (int count = 0; count < LOOP_COUNT; count++)
	{
		Stage1 = NewStage(Stage1);
		
		if (Stage1 != NULL)
		{
			return True;
		}
	}
	printf("방 생성 불가능");
	return False;
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

// door2의 문이 door1의 모든 문을 포함하고 있을 때
// door1이 필요한 문, door2가 확인하고싶은 문
Bool CheckDoor(int door1, int door2)
{
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		// door1에 있는 문이 door2에 없을 때
		if ((door1 & (1 << direction)) > (door2 & (1 << direction)))
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
		RenderStage(0, 0, stage);
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
			printf("방이 없어요 %d, %d\n",roomCount, stage->roomCount);
			Sleep(1000);
			for (int i = 0; i < stage->roomCount; i++)
			{
				free(stage->rooms[i]);
			}
			free(stage->rooms);
			stage->roomCount = 0;
			return NULL;
		}
		printf("스테이지 생성 성공\n");
		Sleep(1000);
		break;
	}
	return stage;
}

void InitializeRoomInfo()
{
	/*Room* room = NewRoomInfo();
	SaveRoomInfoFile("001", room);*/
	RoomInfos = (RoomInfo**)malloc(sizeof(RoomInfo*));
	if (RoomInfos == NULL) { return; }

	char name[10] = "";
	for (int i = 0; 1; i++)
	{
		sprintf(name, "%03d", i);
		RoomInfo* roomInfo = LoadRoomInfoFile(name);
		if (roomInfo == NULL) { return; }
		Sleep(100);
		++RoomInfoCount;
		AddRoomInfo(roomInfo);
	}
}

// 초기화된 방 정보를 생성
RoomInfo* NewRoomInfo()
{
	RoomInfo* room = (RoomInfo*)malloc(sizeof(RoomInfo));
	if (room == NULL) { return; }
	room->type = ROOM_START;
	room->width = ROOM_WIDTH;
	room->height = ROOM_HEIGHT;
	room->percentage = 10;
	room->tile = NewArray(room->width, room->height);
	room->tag = NewArray(room->width, room->height);
	room->monsterCount = 0;
	room->monsters = NewArray(room->width, room->height);
	room->door = 0;
	for (int direction = 0; direction < DIRECTION_COUNT; direction++)
	{
		room->door = room->door | (1 << direction);
	}
	return room;
}

// 방정보에 방을 추가하는 메소드
void AddRoomInfo(RoomInfo* room)
{
	if (RoomInfos == NULL) { return; }
	RoomInfos = (RoomInfo**)realloc(RoomInfos, sizeof(RoomInfo*) * RoomInfoCount);
	if (RoomInfos == NULL) { return; }
	RoomInfos[RoomInfoCount - 1] = room;
}

// 맵 정보의 인덱스를 랜덤으로 생성해주는 메소드
int RandomRoom(RoomType type)
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
		if (sumPercentage < RoomInfos[i]->percentage)
		{
			return i;
		}
		sumPercentage -= RoomInfos[i]->percentage;
	}
	return -1;
}

// RoomInfos의 인덱스와 문 정보를 파라미터로 방을 생성한 뒤 반환하는 메소드
Room* NewRoom(int index, Door door)
{
	Room* room = (Room*)malloc(sizeof(Room));
	if (room == NULL) { return NULL; }

	room->type = RoomInfos[index]->type;
	room->width = RoomInfos[index]->width;
	room->height = RoomInfos[index]->height;
	room->door = RoomInfos[index]->door;
	room->tile = DuplicateArray(RoomInfos[index]->tile, room->width, room->height);
	room->tag = DuplicateArray(RoomInfos[index]->tag, room->width, room->height);
	room->clear = RoomInfos[index]->monsterCount == 0;
	room->monsters = (Creature**)malloc(sizeof(Creature*) * RoomInfos[index]->monsterCount);
	room->monsterCount = 0;
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			int id;
			if (id = RoomInfos[index]->monsters[x][y] < 0)
			{
				continue;
			}
			Creature* monster = NewMonster(id);
			monster->object.position.x = x;
			monster->object.position.y = y;
			room->monsters[room->monsterCount++] = monster;
		}
	}

	return room;
}

// 스테이지에 방을 추가하는 메소드
void AddRoom(Stage* stage, Room* room)
{
	stage->rooms = (Room**)realloc(stage->rooms, sizeof(Room*) * ++stage->roomCount);
	if (stage->rooms == NULL) { return; }
	stage->rooms[stage->roomCount - 1] = room;
}

void CheckProjectile(Room* room, Projectile* projectile)
{
	Coordination zero = { 0,0 };
	for (int i = 1; i < room->monsterCount; i++)
	{
		if (room->monsters[i]->enable == True)
		{
			if (CheckCollider(&projectile->object, &room->monsters[i]->object, zero) == True)
			{
				HitProjectile(projectile, room->monsters[i]);
			}
		}
	}
}

void ProcessMonster(Room* room)
{
	for (int i = 0; i < room->monsterCount; i++)
	{
		if (room->monsters[i]->enable)
		{
			Coordination direction = NewCoordination(RandomRange(-1, 1), RandomRange(-1, 1));
			direction = MultiplyCoordination(direction, room->monsters[i]->speed);
			direction = CheckMove(room, room->monsters[i]->id, &(room->monsters[i]->object), direction);
			room->monsters[i]->object.position = AddCoordination(room->monsters[i]->object.position, direction);
		}
	}
}

void ProcessProjectile(Room* room)
{
	for (int i = 0; i < ProjectileCount; i++)
	{
		if (Projectiles[i]->enable == True)
		{
			Coordination temp = DIRECTIONS[Projectiles[i]->object.direction];
			temp = MultiplyCoordination(temp, Projectiles[i]->speed);
			Projectiles[i]->object.position = AddCoordination(Projectiles[i]->object.position, temp);
			CheckProjectile(room, Projectiles[i]);
			if (--Projectiles[i]->distance == 0)
			{
				Projectiles[i]->enable = False;
			}
		}
	}
}

Coordination CheckMove(Room* room, int id, Object* object, Coordination direction)
{
	Coordination temp = { 0, 0 };
	for (int i = 0; i < room->monsterCount; i++)
	{
		// 몬스터의 id가 자신이거나 비활성화 돼있을 때 스킵
		if (room->monsters[i]->id == id || !room->monsters[i]->enable || (object->layer != room->monsters[i]->object.layer))
		{
			continue;
		}
		temp.x = direction.x;
		temp.y = 0;
		if (CheckCollider(object, &(room->monsters[i]->object), temp))
		{
			direction.x = 0;
		}
		temp.x = 0;
		temp.y = direction.y;
		if (CheckCollider(object, &(room->monsters[i]->object), temp))
		{
			direction.y = 0;
		}
	}
	return direction;
}
