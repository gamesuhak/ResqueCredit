#include <Windows.h>
#include "Render.h"
#include "Object.h"
#include "Input.h"
//#include "Data.h"

// �ڷ��� bool�� ����� �� �ֵ��� ���� �� ����
typedef enum bool{ false = 0, true } bool;

int MapID;

int PlayerX; // �÷��̾��� X��ǥ
int PlayerY; // �÷��̾��� Y��ǥ
int PlayerHP; // �÷��̾��� ü��
int PlayerPower; // ��
int PlayerSpeed;
int PlayerAttackSpeed;

int main()
{
	Render();
}