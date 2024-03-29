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
#include "Sound.h"

extern TitleMenuType TitleMenu;
SceneType Scene = SCENE_TITLE;
Bool Pause = False;

int Random(int value)
{
	return (rand() % value);
} // 참고 : https://edu.goorm.io/learn/lecture/201/%ED%95%9C-%EB%88%88%EC%97%90-%EB%81%9D%EB%82%B4%EB%8A%94-c%EC%96%B8%EC%96%B4-%EA%B8%B0%EC%B4%88/lesson/12382/%EB%82%9C%EC%88%98-%EB%9E%9C%EB%8D%A4-%EB%A7%8C%EB%93%A4%EA%B8%B0

int RandomRange(int start, int end)
{
	return ((rand() % (end - start + 1)) + start);
}

int main()
{
	srand(time(NULL)); // 랜덤시드 현재 시간으로 초기화

	InitializeKey(); // 키 초기화
	InitializeMonsterInfo(); // 몬스터 정보 초기화
	InitializeRoomInfo(); // 방 정보 초기화

	InitializeFMODSound(); // 사운드 초기화 
	
	InitializeScreen(); // 화면 초기화
	InitializeSprites(); // 스프라이트들 초기화
	InitializeRender(); // 렌더링 초기화
	
	InitilizeTitle(); // 타이틀 초기화

	// 스레드 실행
	Thread(InputProcess); // 입력 프로세스를 스레드로 실행
	Thread(Render); // 
	TitleProcess(); // 타이틀 실행
	
	if (TitleMenu == TITLEMENU_GAME)
	{
		if (InitializeStage())
		{
			InitializePlayer(); // 플레이어를 초기화
			Thread(ProcessRoom); // 방 처리 스레드로 실행
			
			Scene = SCENE_GAME;
			SetInputHandler(PlayerMove); // 입력 핸들러에 플레이어 이동 메소드를 연결
		}
	}
	else if (TitleMenu == TITLEMENU_EDIT)
	{
		Scene = SCENE_EDIT;
	}
	else if (TitleMenu == TITLEMENU_EXIT)
	{
		exit(0);
	}
	while (True) {}
}