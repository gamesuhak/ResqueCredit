#include "Object.h"
Creature* Monsters;
typedef enum bool{ false = 0, true } bool;
struct Creature
{
	int x;
	int y;
	int hp;
	int power;
	int speed;
	bool enable;
};

struct Object
{
	int x;
	int y;

};

Creature* CreateMonster()
{
	Creature monster;
	return &monster;
}