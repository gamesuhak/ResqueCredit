#include <Windows.h>
#include <time.h> // time
#include "Render.h"
#include "Object.h"
#include "Input.h"
#include "Thread.h"
#include "Bool.h"
#include "Map.h"
#include "Function.h"

extern Creature** Monsters;
extern Creature* Player;
extern Bool KeyState[KEY_COUNT];
extern int KeyCharge[KEY_COUNT];
extern char ASCIIMODE;

int Random(int value)
{
	return (rand() % value);
} // 참고 : https://edu.goorm.io/learn/lecture/201/%ED%95%9C-%EB%88%88%EC%97%90-%EB%81%9D%EB%82%B4%EB%8A%94-c%EC%96%B8%EC%96%B4-%EA%B8%B0%EC%B4%88/lesson/12382/%EB%82%9C%EC%88%98-%EB%9E%9C%EB%8D%A4-%EB%A7%8C%EB%93%A4%EA%B8%B0

int RandomRange(int start, int end)
{
	return ((rand() % (end - start + 1)) + start);
}

void Move()
{
	int cooltime = 0;
	while (1)
	{
		Coordination move = { 0,0 };
		if (KeyState[KEY_C])
		{
			ASCIIMODE = !ASCIIMODE;
		}
		if (KeyState[KEY_UP])
		{
			if ((KeyCharge[KEY_UP] < KeyCharge[KEY_DOWN]) || !KeyState[KEY_DOWN])
			{
				move.y = -1;
			}
		}
		if (KeyState[KEY_DOWN])
		{
			if ((KeyCharge[KEY_DOWN] < KeyCharge[KEY_UP]) || !KeyState[KEY_UP])
			{
				move.y += 1;
			}
		}
		if (KeyState[KEY_LEFT])
		{
			if ((KeyCharge[KEY_LEFT] < KeyCharge[KEY_RIGHT]) || !KeyState[KEY_RIGHT])
			{
				move.x -= 1;
			}
		}
		if (KeyState[KEY_RIGHT])
		{
			if ((KeyCharge[KEY_RIGHT] < KeyCharge[KEY_LEFT]) || !KeyState[KEY_LEFT])
			{
				move.x += 1;
			}
		}
		if (KeyState[KEY_A])
		{
			if (--cooltime <= 0)
			{
				cooltime = 5;
				ShootProjectile(Player->object.position, Player->object.direction, 0, 1, 2);
			}
		}
		if (move.x != 0 || move.y != 0)
		{
			move = CheckMove(0, &Player->object, move);
			Player->object.position.x += move.x;
			Player->object.position.y += move.y;
			Player->object.direction = move;
			//printf("플레이어 방향 x : %d, y : %d", Player->direction.x, Player->direction.y);
			//printf("플레이어 x : %d, y : %d", Player->object.position.x, Player->object.position.y);
		}
		Sleep(50);
	}
}

int main()
{
	srand(time(NULL));
	Thread(Input);
	Thread(ProcessObject);
	Thread(Move);
	Thread(Render);
	if (InitializeStage())
	{
		
	}
	while (1)
	{

	}
}