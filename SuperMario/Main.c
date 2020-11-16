//#include <Windows.h>
#include <time.h> // time
#include "Render.h" // Render
#include "Object.h" // ProcessRoom
#include "Input.h" // InputProcess
#include "Thread.h" // Thread
#include "Stage.h" // InitializeStage
#include "Room.h"
#include "Function.h" // Random, RandomRange
#include "Player.h" // InitializePlayer, PlayerMove

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
	srand(time(NULL));

	InitializeKey(); // 키를 초기화
	InitializeMonsterInfo(); // 몬스터 정보를 초기화
	InitializeRoomInfo(); // 방 정보를 초기화

	Thread(InputProcess); // 입력 프로세스를 스레드로 실행

	if (InitializeStage())
	{
		InitializePlayer(); // 플레이어를 초기화
		SetInputHandler(PlayerMove); // 입력 핸들러에 플레이어 이동 메소드를 연결
		Thread(ProcessRoom);
		Thread(Render);
	}
	while (1)
	{

	}
}