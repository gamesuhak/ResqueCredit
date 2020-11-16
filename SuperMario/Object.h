#pragma once
#include "Bool.h"
#include "Image.h"
#include "Animator.h"
#include "Coordination.h"
#include "State.h"

#define OBJECTPOOL_COUNT	10
#define PLAYER_HP_MAX		6

typedef struct MonsterInfo MonsterInfo;
typedef struct Creature Creature;
typedef struct Projectile Projectile;
typedef struct Object Object;
typedef struct Collider Collider;

typedef enum Direction { DIRECTION_DOWN = 0, DIRECTION_LEFT, DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_COUNT } Direction;
typedef enum ObjectType { TYPE_MONSTER = 0, TYPE_ITEM, TYPE_PROJECTILE, TYPE_COUNT } ObjectType;
typedef enum ProjectileType { PROJECTILE_BULLET = 0, PROJECTILE_ARROW, PROJECTILE_MISSILE, PROJECTILE_COUNT } ProjectileType;

struct Collider
{
	Coordination pivot; // 콜라이더의 중심점
	Coordination size; // 콜라이더의 크기
};

struct Object
{
	int type;
	int sprite; // 스프라이트 번호
	State state;
	char layer; // 오브젝트가 존재하는 레이어
	Coordination position; // 오브젝트의 위치
	Direction direction; // 오브젝트의 방향
	Collider collider; // 오브젝트의 콜라이더
	Animator* animator; // 애니메이터
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
	Bool enable;
	Object object;
};

struct Projectile
{
	short power;
	short speed;
	short distance; // 나아갈 수 있는 거리
	short penetration; // 몇번 관통할 수 있는지
	Bool throughWall;
	Bool enable;
	Object object;
};

void InitializeObject();

void InitializeMonsterInfo();
void AddMonsterInfo(Creature* monster);

Creature* NewCreature();
Creature* NewMonster(int id);

void DisableProjectile();
void ShootProjectile(Coordination position, Direction direction, ProjectileType type, int power, int speed);
void HitProjectile(Projectile* bullet, Creature* target);
Projectile* NewProjectile();
Projectile* GetProjectile();

Bool CheckCollider(Object* object1, Object* object2, Coordination offset);
void UpdateAnimator(Object* object);