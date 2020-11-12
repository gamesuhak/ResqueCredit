#include "Object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memset
#include "Function.h"

Creature* Player; // �÷��̾� ��ü�� ������ ������
Creature** Monsters; // ���͸� ������ ���� ������
Projectile** Projectiles; // �߻�ü ������ �迭
int MonsterInfoCount = 0;
int CreatureCount = 0;
int ProjectileCount = 0;

void ProcessObject()
{
	InitializeObject();
	while (1)
	{
		ProcessMonster();
		ProcessProjectile();
		Sleep(100);
	}
}

void InitializeObject()
{
	Player = NewCreature();
	Player->enable = True;
	Player->object.position.x = 40;
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
	Monsters[1]->hp = 10;

	Projectiles = (Projectile**)malloc(sizeof(Projectile*) * MONSTER_COUNT);
	if (Projectiles == NULL) { return; }

	for (int i = 0; i < MONSTER_COUNT; i++)
	{
		Projectiles[i] = NewProjectile();
	}
}

void ProcessMonster()
{
	for (int i = 1; i < CreatureCount; i++)
	{
		if (Monsters[i]->enable)
		{
			Coordination temp = { 0,0 };
			if (Random(2))
			{
				temp.x = RandomRange(-1, 1);
			}
			else
			{
				temp.y = RandomRange(-1, 1);
			}
			temp = CheckMove(Monsters[i]->id, &Monsters[i]->object, temp);
			if (temp.x == 0 && temp.y == 0)
			{

			}
			Monsters[i]->object.position.x += temp.x;
			Monsters[i]->object.position.y += temp.y;
		}
	}
}

void ProcessProjectile()
{
	for (int i = 0; i < ProjectileCount; i++)
	{
		if (Projectiles[i]->enable == True)
		{
			Coordination temp = { 0,0 };
			temp = Projectiles[i]->object.direction;
			temp.x *= Projectiles[i]->speed;
			temp.y *= Projectiles[i]->speed;
			Projectiles[i]->object.position.x += temp.x;
			Projectiles[i]->object.position.y += temp.y;
			CheckProjectile(Projectiles[i]);
			if (--Projectiles[i]->distance == 0)
			{
				Projectiles[i]->enable = False;
			}
		}
	}
}

void ShootProjectile(Coordination position, Coordination direction, ProjectileType type, int power, int speed)
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
	projectile->object.collider.pivot.x = 4;
	projectile->object.collider.pivot.y = 4;
	projectile->object.collider.size.x = 8;
	projectile->object.collider.size.y = 8;
	return projectile;
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

// ũ���ĸ� �����ϴ� �޼ҵ�
Creature* NewCreature()
{
	Creature* creature = (Creature*)malloc(sizeof(Creature));
	if (creature == NULL) { return NULL; }
	memset(creature, 0, sizeof(Creature));
	creature->id = CreatureCount++;
	creature->enable = False;
	creature->object.layer = 0;
	creature->object.collider.pivot.x = 4;
	creature->object.collider.pivot.y = 4;
	creature->object.collider.size.x = 8;
	creature->object.collider.size.y = 8;
	return creature;
}

// 
Creature* GetCreature()
{
	for (int i = 0; i < CreatureCount; i++)
	{
		if (Monsters[i]->enable == False)
		{
			return Monsters[i];
		}
	}
	return NewCreature();
}

// id������ ũ���� ã��
Creature* FindCreature(int id)
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

Coordination CheckMove(int id, Object* object, Coordination direction)
{
	Coordination temp = { 0, 0 };
	for (int i = 0; i < CreatureCount; i++)
	{
		// ������ id�� �ڽ��̰ų� ��Ȱ��ȭ ������ �� ��ŵ
		if (Monsters[i]->id == id || !Monsters[i]->enable || (object->layer != Monsters[i]->object.layer))
		{
			continue;
		}
		temp.x = direction.x;
		temp.y = 0;
		if (CheckCollider(object, &Monsters[i]->object, temp))
		{
			direction.x = 0;
		}
		temp.x = 0;
		temp.y = direction.y;
		if (CheckCollider(object, &Monsters[i]->object, temp))
		{
			direction.y = 0;
		}
	}
	return direction;
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

void CheckProjectile(Projectile* projectile)
{
	Coordination zero = { 0,0 };
	for (int i = 1; i < CreatureCount; i++)
	{
		if (Monsters[i]->enable == True)
		{
			if (CheckCollider(&projectile->object, &Monsters[i]->object, zero) == True)
			{
				HitProjectile(projectile, Monsters[i]);
			}
		}
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