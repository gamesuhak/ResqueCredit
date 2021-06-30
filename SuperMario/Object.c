#include "Object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset
#include "Function.h"
#include "FileLoader.h" // LoadMonsterInfoFile
#include "Sprite.h"
#include "Sound.h"

const Coordination DIRECTIONS[DIRECTION_COUNT] =
{
	{0, 1}, {-1, 0}, {0, -1}, {1, 0}
};

MonsterInfo** MonsterInfos = NULL; // ���� �������� ������ MonsterInfo 2���� ������
Projectile** Projectiles = NULL; // �߻�ü ������ �迭
int MonsterInfoCount = 0; // ���� ������ ������ ������ ����
int ProjectileCount = 0; // �߻�ü ������ ������ ����

void InitializeMonsterInfo()
{
	//MonsterInfo* monsterInfo = NewMonsterInfo();
	//SaveMonsterInfoFile("001", monsterInfo);
	MonsterInfos = (MonsterInfo**)malloc(sizeof(MonsterInfo*));
	if (MonsterInfos == NULL) { return NULL; }

	char name[10] = "";
	for (int i = 0; 1; i++)
	{
		sprintf(name, "%03d", i);
		MonsterInfo* monsterInfo = LoadMonsterInfoFile(name);
		if (monsterInfo == NULL) { return; }
		++MonsterInfoCount;
		AddMonsterInfo(monsterInfo);
	}
}

// �ʱ�ȭ�� �� ������ ����
MonsterInfo* NewMonsterInfo()
{
	MonsterInfo* monsterInfo = (MonsterInfo*)malloc(sizeof(MonsterInfo));
	if (monsterInfo == NULL) { return; }
	monsterInfo->hp = 0;
	monsterInfo->power = 0;
	monsterInfo->object.collider.pivot.x = 4;
	monsterInfo->object.collider.pivot.y = 4;
	monsterInfo->object.collider.size.x = 8;
	monsterInfo->object.collider.size.y = 8;
	monsterInfo->object.sprite = SPRITE_BULLET;
	monsterInfo->object.direction = DIRECTION_DOWN;
	monsterInfo->object.layer = 0;
	monsterInfo->object.state = STATE_IDLE;
	monsterInfo->object.animator = NULL;
	monsterInfo->projectile = 0;
	return monsterInfo;
}

void AddMonsterInfo(MonsterInfo* monster)
{
	if (MonsterInfos == NULL) { return NULL; }
	MonsterInfos = (MonsterInfo**)realloc(MonsterInfos, sizeof(MonsterInfo*) * MonsterInfoCount);
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

void ShootProjectile(int from, Coordination position, Direction direction, ProjectileType type, int power, int speed)
{
	Projectile* projectile;
	projectile = GetProjectile();
	projectile->from = from;
	projectile->object.position = position;
	projectile->object.direction = direction;
	projectile->power = power;
	projectile->speed = speed;
	projectile->penetration = 1;
	projectile->distance = 50;
	projectile->enable = True;
	if (type == PROJECTILE_BULLET)
	{
		int frame = 1;
		projectile->object.sprite = SPRITE_BULLET;
		projectile->object.animator = NewAnimator(SPRITE_BULLET, 1, 1, 20, &frame);
	}
	else if (type == PROJECTILE_ARROW)
	{
		int frame = 1;
		projectile->object.sprite = SPRITE_ARROW;
		projectile->object.animator = NewAnimator(SPRITE_ARROW, 1, DIRECTION_COUNT, 20, &frame);
	}
	else if (type == PROJECTILE_SWORD)
	{
		int frame = 1;
		projectile->object.sprite = SPRITE_SWORD;
		projectile->object.animator = NewAnimator(SPRITE_ARROW, 1, DIRECTION_COUNT, 20, &frame);
	}
}

Projectile* NewProjectile()
{
	Projectile* projectile = (Projectile*)malloc(sizeof(Projectile));
	if (projectile == NULL) { return NULL; }
	memset(projectile, 0, sizeof(Projectile));
	ProjectileCount++;
	projectile->enable = False;
	projectile->object.layer = 0;
	projectile->object.state = STATE_IDLE;
	projectile->object.direction = DIRECTION_DOWN;
	projectile->object.collider.pivot.x = 2;
	projectile->object.collider.pivot.y = 2;
	projectile->object.collider.size.x = 4;
	projectile->object.collider.size.y = 4;
	return projectile;
}

Creature* NewCreature()
{
	Creature* creature = (Creature*)malloc(sizeof(Creature));
	if (creature == NULL) { return NULL; }
	memset(creature, 0, sizeof(Creature));
	creature->type = MONSTER_BUBBLUN;
	creature->hp = 0;
	creature->cooltime = 0;
	creature->enable = False;
	creature->object.sprite = SPRITE_BULLET;
	creature->object.direction = DIRECTION_DOWN;
	creature->object.layer = 0;
	creature->object.state = STATE_IDLE;
	creature->object.collider.pivot.x = 4;
	creature->object.collider.pivot.y = 4;
	creature->object.collider.size.x = 8;
	creature->object.collider.size.y = 8;
	creature->object.animator = NULL;
	creature->projectile = 0;
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
	// ��Ȱ��ȭ �� ����ü�� ã�� ���Ͽ��� ��
	// realloc�̿��ؼ� �迭�� �߰��ϵ��� �����ϱ�
	Projectile* projectile = NewProjectile();
	Projectiles = (Projectile**)realloc(Projectiles, sizeof(Projectile*) * ProjectileCount);
	Projectiles[ProjectileCount - 1] = projectile;
	return projectile;
}

// id�� ���͸� �����ϴ� �޼ҵ�
Creature* NewMonster(int id)
{
	Creature* creature = NewCreature();
	if (creature == NULL) { return NULL; }
	creature->type = MonsterInfos[id]->type;
	creature->hp = MonsterInfos[id]->hp;
	creature->power = MonsterInfos[id]->power;
	creature->speed = MonsterInfos[id]->speed;
	creature->object = MonsterInfos[id]->object;
	creature->projectile = MonsterInfos[id]->projectile;
	int sprite = SPRITE_KIRBY;
	int frame[2] = { 4, 4 };
	if (creature->type == MONSTER_BUBBLUN)
	{
		creature->object.sprite = SPRITE_BUBBLUN;
		//creature->object.animator = NewAnimator(SPRITE_BUBBLUN, STATE_WALK + 1, DIRECTION_COUNT, 20, frame);
	}
	else if (creature->type == MONSTER_CREW)
	{
		creature->object.sprite = SPRITE_CREW;
	}
	else if (creature->type == MONSTER_GHOST)
	{
		creature->object.sprite = SPRITE_GHOST;
	}
	else if (creature->type == MONSTER_KIRBY)
	{
		creature->object.sprite = SPRITE_KIRBY;
	}
	
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

// object1�� offset�� ���� ��ġ�� object2�� �浹���ִ��� �Ǻ��ϴ� �Լ�
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
	if (object->animator == NULL)
	{
		return;
	}

	// ������Ʈ�� ���°� ������ ��
	if (object->state != object->animator->state)
	{
		// �ִϸ������� ���¸� ����, ��� �ð� �ʱ�ȭ
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