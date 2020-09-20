#include <Windows.h>
#include "Render.h"
#include "Object.h"
#include "Input.h"
//#include "Data.h"

// 자료형 bool을 사용할 수 있도록 선언 및 정의
typedef enum bool{ false = 0, true } bool;

int MapID;

int PlayerX; // 플레이어의 X좌표
int PlayerY; // 플레이어의 Y좌표
int PlayerHP; // 플레이어의 체력
int PlayerPower; // 플
int PlayerSpeed;
int PlayerAttackSpeed;

int main()
{
	Render();
}