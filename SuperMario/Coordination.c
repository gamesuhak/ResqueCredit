#include "Coordination.h"

// 두 좌표를 받아 Coordination으로 반환하는 메소드
Coordination NewCoordination(int x, int y)
{
	Coordination coordination = { x, y };
	return coordination;
}

// 두 좌표의 합을 반환하는 메소드
Coordination AddCoordination(Coordination coordination1, Coordination coordination2)
{
	coordination1.x += coordination2.x;
	coordination1.y += coordination2.y;
	return coordination1;
}

// 좌표에 스칼라 값 곱을 반환하는 메소드
Coordination MultiplyCoordination(Coordination coordination, int scalar)
{
	coordination.x *= scalar;
	coordination.y *= scalar;
	return coordination;
}

// 좌표에 스칼라로 나누어 반환하는 메소드
Coordination DivideCoordination(Coordination coordination, int scalar)
{
	coordination.x = (int)(coordination.x / (float)scalar);
	coordination.y = (int)(coordination.y / (float)scalar);
	return coordination;
}

// 좌표의 반대를 반환하는 메소드
Coordination InverseCoordination(Coordination coordination)
{
	coordination.x *= -1;
	coordination.y *= -1;
	return coordination;
}

// 두 좌표가 같으면 참을 반환하는 메소드
Bool CompareCoordination(Coordination coordination1, Coordination coordination2)
{
	if (coordination1.x == coordination2.x && coordination1.y == coordination2.y)
	{
		return True;
	}
	else
	{
		return False;
	}
}