#pragma once
#include "Bool.h"
#include "Image.h"
#include "Animator.h"
#include "Coordination.h"
#define MONSTER_COUNT		10
#define PLAYER_HP_MAX		6

typedef struct MonsterInfo MonsterInfo;
typedef struct Creature Creature;
typedef struct Projectile Projectile;
typedef struct Object Object;
typedef struct Collider Collider;

typedef enum Direction { DIRECTION_UP = 0, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_COUNT } Direction;
typedef enum ObjectType { TYPE_MONSTER = 0, TYPE_ITEM, TYPE_PROJECTILE, TYPE_COUNT } ObjectType;
typedef enum ProjectileType { PROJECTILE_BULLET = 0, PROJECTILE_ARROW, PROJECTILE_MISSILE, PROJECTILE_COUNT } ProjectileType;
typedef enum AnimationType { ANIMATION_BULLET = 0 } AnimationType;
typedef enum State { STATE_IDLE = 0, STATE_WALK, STATE_ATTACK, STATE_COUNT };
typedef enum Pivot { PIVOT_LEFTUP = 0, PIVOT_MIDDLE};



struct Collider
{
	Coordination pivot; // 콜라이더의 중심점
	Coordination size; // 콜라이더의 크기
};

struct Object
{
	int type;
	char layer; // 오브젝트가 존재하는 레이어
	Coordination position; // 오브젝트의 위치
	Coordination direction; // 오브젝트의 방향
	Collider collider; // 오브젝트의 콜라이더
};

struct MonsterInfo
{
	short id;
	int hp;
	int power;
	int speed;
	int sprite;
	Object object;
	Coordination position;
};

struct Creature
{
	short id;
	int hp;
	int power;
	int speed;
	int sprite; // 현재 스프라이트 번호
	int state;
	//Sprite sprite;
	bool enable;
	Object object;
	Animator* animator;
};

struct Projectile
{
	short power;
	short speed;
	short distance; // 나아갈 수 있는 거리
	short penetration; // 몇번 관통할 수 있는지
	bool throughWall;
	bool enable;
	Object object;
};

struct Animation
{
	char currentFrame;
	AnimationType type;
	Object object;
};

void InitializeObject();

void ProcessObject();
void ProcessMonster();
void ProcessProjectile();

void ShootProjectile(Coordination position, Coordination direction, ProjectileType type, int power, int speed);

void CheckProjectile(Projectile* projectile);
void HitProjectile(Projectile* bullet, Creature* target);

Creature* NewCreature();
Creature* GetCreature();
Creature* FindCreature(int id);

Projectile* NewProjectile();
Projectile* GetProjectile();

Coordination CheckMove(int id, Object* object, Coordination direction);
bool CheckCollider(Object* object1, Object* object2, Coordination offset);