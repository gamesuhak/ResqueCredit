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

// �ڷ��� bool�� ����� �� �ֵ��� ���� �� ����
typedef enum bool{ false = 0, true } bool;
int MapID;

int PlayerAttackSpeed;

int main()
{
	Render();
}