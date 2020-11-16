//#include <Windows.h>
#include <time.h> // time
#include "Screen.h"
#include "Sprite.h"
#include "Render.h" // Render
#include "Object.h" // ProcessRoom
#include "Input.h" // InputProcess
#include "Thread.h" // Thread
#include "Stage.h" // InitializeStage
#include "Room.h"
#include "Function.h" // Random, RandomRange
#include "Player.h" // InitializePlayer, PlayerMove
#include "Title.h"
#include "GameData.h"
#include <stdio.h>

extern TitleMenuType TitleMenu;
SceneType Scene = SCENE_TITLE;
Bool Pause = False;
Bool IsProcess = True;

int Random(int value)
{
	return (rand() % value);
} // ���� : https://edu.goorm.io/learn/lecture/201/%ED%95%9C-%EB%88%88%EC%97%90-%EB%81%9D%EB%82%B4%EB%8A%94-c%EC%96%B8%EC%96%B4-%EA%B8%B0%EC%B4%88/lesson/12382/%EB%82%9C%EC%88%98-%EB%9E%9C%EB%8D%A4-%EB%A7%8C%EB%93%A4%EA%B8%B0

int RandomRange(int start, int end)
{
	return ((rand() % (end - start + 1)) + start);
}

int main()
{
	srand(time(NULL)); // �����õ带 ���� �ð����� �ʱ�ȭ

	InitializeKey(); // Ű�� �ʱ�ȭ
	InitializeMonsterInfo(); // ���� ������ �ʱ�ȭ
	InitializeRoomInfo(); // �� ������ �ʱ�ȭ

	InitializeScreen(); // ȭ�� �ʱ�ȭ
	InitializeSprites(); // ��������Ʈ�� �ʱ�ȭ
	InitializeRender(); // ������ �ʱ�ȭ
	
	//InitilizeTitle(); // Ÿ��Ʋ �ʱ�ȭ
	
	// ������ ����
	Thread(InputProcess); // �Է� ���μ����� ������� ����
	//Thread(TitleProcess);
	
	if (InitializeStage())
	{
		Scene = SCENE_GAME;
		InitializePlayer(); // �÷��̾ �ʱ�ȭ
		SetInputHandler(PlayerMove); // �Է� �ڵ鷯�� �÷��̾� �̵� �޼ҵ带 ����
		Thread(ProcessRoom);
		Thread(Render);
		
	}
	
	while (IsProcess) {}
	/*while (IsProcess) {}

	if (TitleMenu == TITLEMENU_GAME)
	{
		
	}
	else if (TitleMenu == TITLEMENU_EDIT)
	{
		Scene = SCENE_EDIT;
	}
	else if (TitleMenu == TITLEMENU_EXIT)
	{
		exit(0);
	}
	while (True)
	{
		printf("�ƹ��͵�����\n");
	}*/
}