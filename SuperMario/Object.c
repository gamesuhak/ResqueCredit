#include "Object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset

Creature* Player; // 플레이어 객체를 저장할 
Creature** Monsters; // 몬스터 리스트
int CreatureCount = 0;

void ProcessObject()
{
	InitializeObject();
	TestObject();
	while (1)
	{
	}
}

void TestObject()
{
	for (int i = 0; i < MONSTER_COUNT; i++)
	{
		if (Monsters[i]->enable)
		{
			//printf("아이디 : %d , x : %d, y : %d", Monsters[i]->id, Monsters[i]->object.position.x, Monsters[i]->object.position.y);
		}
	}
}

void InitializePlayer()
{
	Player = CreateCreature();
	Player->object.position.x = 40;
	Player->object.position.y = 32;
}

void InitializeObject()
{
	InitializePlayer();
	Monsters = (Creature**)malloc(sizeof(Creature*) * MONSTER_COUNT);
	if (Monsters == NULL) { return; }
	for (int i = 0; i < MONSTER_COUNT; i++)
	{
		Monsters[i] = CreateCreature();
	}
	Monsters[1]->object.position.x = 16;
	Monsters[1]->object.position.y = 32;
	Monsters[1]->enable = true;

	Monsters[2]->object.position.x = 48;
	Monsters[2]->object.position.y = 32;
	Monsters[2]->enable = true;
}

Creature* CreateCreature()
{
	Creature* creature = (Creature*)malloc(sizeof(Creature));
	if (creature == NULL) { return NULL; }
	memset(creature, 0, sizeof(Creature));
	creature->id = CreatureCount++;
	creature->enable = false;
	creature->object.collider.pivot.x = 4;
	creature->object.collider.pivot.y = 4;
	creature->object.collider.size.x = 8;
	creature->object.collider.size.y = 8;
	return creature;
}

Creature* GetCreature(int id)
{
	for (int i = 0; i < CreatureCount; i++)
	{
		if (Monsters[i]->id == id)
		{
			return Monsters[i];
		}
	}
	return NULL;
}

Coordination CheckCollider(int id, Object* object, Coordination direction)
{
	// 오브젝트 콜라이더의 중점의 계산
	float pivotx = object->position.x - object->collider.pivot.x + (object->collider.size.x * 0.5f); // + direction.x;
	float pivoty = object->position.y - object->collider.pivot.y + (object->collider.size.y * 0.5f); // + direction.y;
	float distancex;
	float distancey;
	for (int i = 0; i < CreatureCount - 1; i++)
	{
		// 몬스터의 id가 자신이거나 비활성화 돼있을 때 스킵
		if (Monsters[i]->id == id || !Monsters[i]->enable)
		{
			continue;
		}
		distancex = Monsters[i]->object.position.x - Monsters[i]->object.collider.pivot.x + Monsters[i]->object.collider.size.x * 0.5f - pivotx - direction.x;
		distancey = Monsters[i]->object.position.y - Monsters[i]->object.collider.pivot.y + Monsters[i]->object.collider.size.y * 0.5f - pivoty;

		distancex = (distancex < 0) ? -distancex : distancex;
		distancey = (distancey < 0) ? -distancey : distancey;
		bool vertical = (distancex < object->collider.size.x * 0.5f + Monsters[i]->object.collider.size.x * 0.5f);
		bool horizontal = (distancey < object->collider.size.y * 0.5f + Monsters[i]->object.collider.size.y * 0.5f);
		if (vertical && horizontal)
		{
			direction.x = 0;
		}

		distancex = Monsters[i]->object.position.x - Monsters[i]->object.collider.pivot.x + Monsters[i]->object.collider.size.x * 0.5f - pivotx;
		distancey = Monsters[i]->object.position.y - Monsters[i]->object.collider.pivot.y + Monsters[i]->object.collider.size.y * 0.5f - pivoty - direction.y;
		distancex = (distancex < 0) ? -distancex : distancex;
		distancey = (distancey < 0) ? -distancey : distancey;
		vertical = (distancex < object->collider.size.x * 0.5f + Monsters[i]->object.collider.size.x * 0.5f);
		horizontal = (distancey < object->collider.size.y * 0.5f + Monsters[i]->object.collider.size.y * 0.5f);
		if (vertical && horizontal)
		{
			direction.y = 0;
		}
	}
	return direction;
}

bool OnCollider(Object* object1, Object* object2)
{
	float pivotx1 = object1->position.x - object1->collider.pivot.x + (object1->collider.size.x * 0.5f);
	float pivoty1 = object1->position.y - object1->collider.pivot.y + (object1->collider.size.y * 0.5f);
	float pivotx2 = object2->position.x - object2->collider.pivot.x + (object2->collider.size.x * 0.5f);
	float pivoty2 = object2->position.y - object2->collider.pivot.y + (object2->collider.size.y * 0.5f);
	pivotx2 -= pivotx1;
	pivoty2 -= pivoty1;
	pivotx2 = (pivotx2 < 0) ? -pivotx2 : pivotx2;
	pivoty2 = (pivoty2 < 0) ? -pivoty2 : pivoty2;
	bool vertical = (pivotx2 < object1->collider.size.x * 0.5f + object2->collider.size.x * 0.5f);
	bool horizontal = (pivoty2 < object1->collider.size.y * 0.5f + object2->collider.size.y * 0.5f);
	return (vertical && horizontal);
}