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

MonsterInfo** MonsterInfos = NULL; // 몬스터 정보들을 저장할 MonsterInfo 2차원 포인터
Projectile** Projectiles = NULL; // 발사체 포인터 배열
int MonsterInfoCount = 0; // 몬스터 정보들 개수를 저장할 변수
int ProjectileCount = 0; // 발사체 개수를 저장할 변수

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
	projectile->distance = 20;
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
	creature->enable = False;
	creature->object.direction = DIRECTION_DOWN;
	creature->object.layer = 0;
	creature->object.state = STATE_IDLE;
	creature->object.collider.pivot.x = 4;
	creature->object.collider.pivot.y = 4;
	creature->object.collider.size.x = 8;
	creature->object.collider.size.y = 8;
	creature->object.animator = NULL;
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

void UpdateAnimator(Object* object)
{
	// 오브젝트의 상태가 변했을 때
	if (object->state != object->animator->state)
	{
		// 애니메이터의 상태를 변경, 재생 시간 초기화
		object->animator->state = object->state;
		object->animator->time = 0;
	}
	int state = (object->state < object->animator->stateCount) ? object->state : object->animator->stateCount - 1;
	int direction = (object->direction < object->animator->animation[state]->directionCount) ? object->direction : 0;//object->animator->animation[state]->directionCount - 1;
	int frame = (object->animator->time / object->animator->frameTime) % (object->animator->animation[state]->frameCount);
	object->sprite = object->animator->animation[state]->clips[frame][direction];
	if (++object->animator->time > object->animator->frameTime * object->animator->animation[state]->frameCount)
	{
		object->animator->time = 0;
	}
}