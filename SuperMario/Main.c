#include <Windows.h>
#include "Render.h"
#include "Object.h"
#include "Input.h"
#include "Thread.h"
#include "Bool.h"


typedef struct Creature
{
	int x;
	int y;
	int hp;
	int power;
	int speed;
};

extern bool KeyState[KEY_COUNT];
extern Creature* Monsters;
extern int PlayerX;
extern int PlayerY;

void Move()
{
	while (1)
	{
		if (KeyState[KEY_UP])
		{
			PlayerY -= 1;
		}
		if (KeyState[KEY_DOWN])
		{
			PlayerY += 1;
		}
		if (KeyState[KEY_LEFT])
		{
			PlayerX -= 1;
		}
		if (KeyState[KEY_RIGHT])
		{
			PlayerX += 1;
		}
		Sleep(100);
	}
}

void PlayerMove()
{
	int self = 0;
	while (true)
	{
		if (++PlayerX >= 50)
		{
			PlayerX = 0;
		}
		//printf("%d : %d\n", self++, PlayerX);
		Sleep(100);
	}
}

int main()
{
	Thread(Input);
	Thread(Move);
	Thread(Render);
	while (1)
	{

	}
	//Key()
}