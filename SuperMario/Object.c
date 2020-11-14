#include "Object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset
#include "Function.h"
#include "FileLoader.h" // LoadMonsterInfoFile

const Coordination DIRECTIONS[DIRECTION_COUNT] =
{
	{0, 1}, {-1, 0}, {0, -1}, {1, 0}
};

extern Creature* Player; // 플레이어 객체를 저장할 포인터

MonsterInfo** MonsterInfos = NULL; // 몬스터 정보들을 저장할 MonsterInfo 2차원 포인터
Projectile** Projectiles = NULL; // 발사체 포인터 배열
int MonsterInfoCount = 0; // 몬스터 정보들 개수를 저장할 변수
int ProjectileCount = 0; // 발사체 개수를 저장할 변수

void ProcessObject()
{
	InitializeObject();
	
	/*while (1)
	{
		ProcessMonster(PlayerRoom);
		ProcessProjectile(PlayerRoom);
		Sleep(100);
	}*/
}

void InitializeMonsterInfo()
{
	MonsterInfos = (MonsterInfo**)malloc(sizeof(MonsterInfo*));
	if (MonsterInfos == NULL) { return NULL; }

	char name[10] = "";
	for (int i = 0; 1; i++)
	{
		sprintf(name, "%03d", i);
		MonsterInfo* monsterInfo = LoadMonsterInfoFile(name);
		if (monsterInfo == NULL) { return; }
		++MonsterInfoCount;
		monsterInfo->object.direction = DIRECTION_DOWN;
		AddMonsterInfo(monsterInfo);
	}
}

void AddMonsterInfo(Creature* monster)
{
	MonsterInfos = (Creature**)realloc(MonsterInfos, sizeof(Creature*) * MonsterInfoCount);
	if (MonsterInfos == NULL) { return NULL; }
	MonsterInfos[MonsterInfoCount - 1] = monster;
}

void InitializeObject()
{
	/*Player->object.position.x = 40;
	Player->object.position.y = 32;

	Monsters = (Creature**)malloc(sizeof(Creature*) * MONSTER_COUNT);
	if (Monsters == NULL) { return; }
	Monsters[0] = Player;

	for (int i = 1; i < MONSTER_COUNT; i++)
	{
		Monsters[i] = NewCreature();
	}
	Monsters[1]->object.position.x = 16;
	Monsters[1]->object.position.y = 32;
	Monsters[1]->enable = True;
	Monsters[1]->hp = 5;

	Monsters[2]->object.position.x = 48;
	Monsters[2]->object.position.y = 32;
	Monsters[2]->enable = True;
	Monsters[1]->hp = 10;*/

	Projectiles = (Projectile**)malloc(sizeof(Projectile*) * OBJECTPOOL_COUNT);
	if (Projectiles == NULL) { return; }
	for (int i = 0; i < OBJECTPOOL_COUNT; i++)
	{
		Projectiles[i] = NewProjectile();
	}
}

void DisableProjectile()
{
	for (int i = 0; i < ProjectileCount; i++)
	{
		Projectiles[i]->enable == False;
	}
}

void ShootProjectile(Coordination position, Direction direction, ProjectileType type, int power, int speed)
{
	Projectile* projectile;
	projectile = GetProjectile();
	projectile->object.position = position;
	projectile->object.direction = direction;
	projectile->power = power;
	projectile->speed = speed;
	projectile->penetration = 1;
	projectile->distance = 15;
	projectile->enable = True;
}

Projectile* NewProjectile()
{
	Projectile* projectile = (Projectile*)malloc(sizeof(Projectile));
	if (projectile == NULL) { return NULL; }
	memset(projectile, 0, sizeof(Projectile));
	ProjectileCount++;
	projectile->enable = False;
	projectile->object.layer = 0;
	projectile->object.direction = DIRECTION_DOWN;
	projectile->object.collider.pivot.x = 4;
	projectile->object.collider.pivot.y = 4;
	projectile->object.collider.size.x = 8;
	projectile->object.collider.size.y = 8;
	return projectile;
}

Creature* NewCreature()
{
	Creature* creature = (Creature*)malloc(sizeof(Creature));
	if (creature == NULL) { return NULL; }
	memset(creature, 0, sizeof(Creature));
	creature->object.direction = DIRECTION_DOWN;
	creature->enable = False;
	creature->object.layer = 0;
	creature->object.collider.pivot.x = 4;
	creature->object.collider.pivot.y = 4;
	creature->object.collider.size.x = 8;
	creature->object.collider.size.y = 8;
	return creature;
}

Projectile* GetProjectile()
{
	for (int i = 0; i < ProjectileCount; i++)
	{
		if (Projectiles[i]->enable == False)
		{
			return Projectiles[i];
		}
	}
	// 비활성화 된 투사체를 찾지 못하였을 때
	// realloc이용해서 배열에 추가하도록 수정하기
	Projectile* projectile = NewProjectile();
	Projectiles = (Projectile**)realloc(Projectiles, sizeof(Projectile*) * ProjectileCount);
	Projectiles[ProjectileCount - 1] = projectile;
	return projectile;
}

// id로 몬스터를 생성하는 메소드
Creature* NewMonster(int id)
{
	Creature* creature = (Creature*)malloc(sizeof(Creature));
	if (creature == NULL) { return NULL; }
	memset(creature, 0, sizeof(Creature));
	//creature->id = CreatureCount++;
	creature->enable = False;
	creature->power = MonsterInfos[id]->power;
	creature->speed = MonsterInfos[id]->speed;
	creature->object = MonsterInfos[id]->object;
	return creature;
}

void HitProjectile(Projectile* bullet, Creature* target)
{
	target->hp -= bullet->power;
	if (--bullet->penetration == 0)
	{
		bullet->enable = False;
	}
	if (target->hp <= 0)
	{
		target->enable = False;
	}
}

// object1에 offset을 더한 위치가 object2와 충돌해있는지 판별하는 함수
Bool CheckCollider(Object* object1, Object* object2, Coordination offset)
{
	float pivotx1 = object1->position.x - object1->collider.pivot.x + (object1->collider.size.x * 0.5f) + offset.x;
	float pivoty1 = object1->position.y - object1->collider.pivot.y + (object1->collider.size.y * 0.5f) + offset.y;
	float pivotx2 = object2->position.x - object2->collider.pivot.x + (object2->collider.size.x * 0.5f);
	float pivoty2 = object2->position.y - object2->collider.pivot.y + (object2->collider.size.y * 0.5f);
	pivotx2 -= pivotx1;
	pivoty2 -= pivoty1;
	pivotx2 = (pivotx2 < 0) ? -pivotx2 : pivotx2;
	pivoty2 = (pivoty2 < 0) ? -pivoty2 : pivoty2;
	Bool vertical = (pivotx2 < object1->collider.size.x * 0.5f + object2->collider.size.x * 0.5f);
	Bool horizontal = (pivoty2 < object1->collider.size.y * 0.5f + object2->collider.size.y * 0.5f);
	return (vertical && horizontal);
}

void UpdateAnimator(Creature* creature)
{

}