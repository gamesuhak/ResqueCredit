#pragma once
#include "Bool.h"
#include "Image.h"
#define MONSTER_COUNT		10

typedef struct Creature Creature;
typedef struct Object Object;
typedef struct Collider Collider;
typedef struct Coordination Coordination;
typedef enum Direction { DIRECTION_UP = 0, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT } Direction;
typedef enum ObjectType { TYPE_MONSTER = 0, TYPE_ITEM, TYPE_BULLET } ObjectType;

struct Coordination
{
	short x;
	short y;
};

struct Collider
{
	Coordination pivot;
	Coordination size;
};

struct Object
{
	int type;
	Coordination position;
	Coordination direction;
	Collider collider;
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

void TestObject();
void ProcessObject();
void InitializeObject();
void InitializePlayer();
Creature* CreateCreature();
Coordination CheckCollider(int id, Object* object, Coordination direction);
bool CheckDistance(Object* object1, Object* object2);
Creature* GetCreature(int id);