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

// �ڷ��� bool�� ����� �� �ֵ��� ���� �� ����
typedef enum bool{ false = 0, true } bool;

//int main()
int main()
{
	Render();
}