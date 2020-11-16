#include "Coordination.h"

// �� ��ǥ�� �޾� Coordination���� ��ȯ�ϴ� �޼ҵ�
Coordination NewCoordination(int x, int y)
{
	Coordination coordination = { x, y };
	return coordination;
}

// �� ��ǥ�� ���� ��ȯ�ϴ� �޼ҵ�
Coordination AddCoordination(Coordination coordination1, Coordination coordination2)
{
	coordination1.x += coordination2.x;
	coordination1.y += coordination2.y;
	return coordination1;
}

// ��ǥ�� ��Į�� �� ���� ��ȯ�ϴ� �޼ҵ�
Coordination MultiplyCoordination(Coordination coordination, int scalar)
{
	coordination.x *= scalar;
	coordination.y *= scalar;
	return coordination;
}

// ��ǥ�� ��Į��� ������ ��ȯ�ϴ� �޼ҵ�
Coordination DivideCoordination(Coordination coordination, int scalar)
{
	coordination.x = (int)(coordination.x / (float)scalar);
	coordination.y = (int)(coordination.y / (float)scalar);
	return coordination;
}

// ��ǥ�� �ݴ븦 ��ȯ�ϴ� �޼ҵ�
Coordination InverseCoordination(Coordination coordination)
{
	coordination.x *= -1;
	coordination.y *= -1;
	return coordination;
}

// �� ��ǥ�� ������ ���� ��ȯ�ϴ� �޼ҵ�
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