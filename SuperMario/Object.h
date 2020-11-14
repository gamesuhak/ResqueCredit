#pragma once
//#include "Map.h" // Room
#include "Bool.h"
#include "Image.h"
#include "Animator.h"
#include "Coordination.h"

#define OBJECTPOOL_COUNT	10
#define PLAYER_HP_MAX		6

typedef struct MonsterInfo MonsterInfo;
typedef struct Creature Creature;
typedef struct Projectile Projectile;
typedef struct Object Object;
typedef struct Collider Collider;

typedef struct Animation Animation;

typedef enum Direction { DIRECTION_DOWN = 0, DIRECTION_LEFT, DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_COUNT } Direction;
typedef enum ObjectType { TYPE_MONSTER = 0, TYPE_ITEM, TYPE_PROJECTILE, TYPE_COUNT } ObjectType;
typedef enum ProjectileType { PROJECTILE_BULLET = 0, PROJECTILE_ARROW, PROJECTILE_MISSILE, PROJECTILE_COUNT } ProjectileType;
typedef enum AnimationType { ANIMATION_BULLET = 0 } AnimationType;

struct Collider
{
	Coordination pivot; // �ݶ��̴��� �߽���
	Coordination size; // �ݶ��̴��� ũ��
};

struct Object
{
	int type;
	char layer; // ������Ʈ�� �����ϴ� ���̾�
	Coordination position; // ������Ʈ�� ��ġ
	Direction direction; // ������Ʈ�� ����
	Collider collider; // ������Ʈ�� �ݶ��̴�
};

struct MonsterInfo
{
	int hp;
	int power;
	int speed;
	int sprite;
	Object object;
};

struct Creature
{
	short id;
	int hp;
	int power;
	int speed;
	//int sprite; // ���� ��������Ʈ ��ȣ
	int state;
	Bool enable;
	Object object;
	Animator* animator;
};

struct Projectile
{
	short power;
	short speed;
	short distance; // ���ư� �� �ִ� �Ÿ�
	short penetration; // ��� ������ �� �ִ���
	Bool throughWall;
	Bool enable;
	Object object;
};

struct Animation
{
	char currentFrame;
	AnimationType type;
	Object object;
};

void InitializeObject();

void InitializeMonsterInfo();
void AddMonsterInfo(Creature* monster);

Creature* NewCreature();
Creature* NewMonster(int id);

void ShootProjectile(Coordination position, Direction direction, ProjectileType type, int power, int speed);
void HitProjectile(Projectile* bullet, Creature* target);
Projectile* NewProjectile();
Projectile* GetProjectile();

Bool CheckCollider(Object* object1, Object* object2, Coordination offset);

void UpdateAnimator(Creature* creature);