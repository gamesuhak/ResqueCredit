#include <Windows.h>
#include "Render.h"
#include "Object.h"
#include "Input.h"

typedef struct Creature
{
	int x;
	int y;
	int hp;
	int power;
	int speed;
};

extern Creature* Monsters;
//#include "Data.h"

// 자료형 bool을 사용할 수 있도록 선언 및 정의
typedef enum bool{ false = 0, true } bool;
int MapID;

int PlayerAttackSpeed;

int main()
{
	Render();
}