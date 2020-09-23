#include <Windows.h>
#include "Render.h"
#include "Object.h"
#include "Input.h"
#include "Thread.h"

typedef struct Creature
{
	int x;
	int y;
	int hp;
	int power;
	int speed;
};

extern Creature* Monsters;
extern int PlayerX;
extern int PlayerY;

// 자료형 bool을 사용할 수 있도록 선언 및 정의
typedef enum bool{ false = 0, true } bool;

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
	Thread(PlayerMove);
	Thread(Render);
	while (1)
	{

	}
	//Key()
}