#pragma once
#include "Bool.h"
#include "Image.h"
#define MONSTER_COUNT		10

typedef struct Creature Creature;
typedef struct Projectile Projectile;
typedef struct Object Object;
typedef struct Collider Collider;
typedef struct Coordination Coordination;
typedef enum Direction { DIRECTION_UP = 0, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT } Direction;
typedef enum ObjectType { TYPE_MONSTER = 0, TYPE_ITEM, TYPE_PROJECTILE } ObjectType;
typedef enum ProjectileType { PROJECTILE_BULLET = 0, PROJECTILE_ARROW, PROJECTILE_MISSILE } ProjectileType;
typedef enum AnimationType { ANIMATION_BULLET = 0 } AnimationType;

struct Coordination
{
	short x;
	short y;
};

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
	Coordination direction; // ������Ʈ�� ����
	Collider collider; // ������Ʈ�� �ݶ��̴�
};

struct Creature
{
	short id;
	int hp;
	int power;
	int speed;
	//Sprite sprite;
	bool enable;
	Object object;
};

struct Projectile
{
	short power;
	short speed;
	short distance; // ���ư� �� �ִ� �Ÿ�
	short penetration; // ��� ������ �� �ִ���
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
Projectile* NewProjectile();
Projectile* CreateProjectile();
void CheckProjectile(Projectile* projectile);
void HitProjectile(Projectile* bullet, Creature* target);

Creature* NewCreature();
Creature* CreateCreature();
Creature* GetCreature(int id);

Coordination CheckMove(int id, Object* object, Coordination direction);
bool CheckCollider(Object* object1, Object* object2, Coordination offset);
