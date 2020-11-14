//#include <Windows.h>
#include <time.h> // time
#include "Render.h" // Render
#include "Object.h" // ProcessObject
#include "Input.h" // Input
#include "Thread.h" // Thread
#include "Map.h" // InitializeStage
#include "Function.h" // Random, RandomRange
#include "Player.h" // InitializePlayer, PlayerMove

int Random(int value)
{
	return (rand() % value);
} // Âü°í : https://edu.goorm.io/learn/lecture/201/%ED%95%9C-%EB%88%88%EC%97%90-%EB%81%9D%EB%82%B4%EB%8A%94-c%EC%96%B8%EC%96%B4-%EA%B8%B0%EC%B4%88/lesson/12382/%EB%82%9C%EC%88%98-%EB%9E%9C%EB%8D%A4-%EB%A7%8C%EB%93%A4%EA%B8%B0

int RandomRange(int start, int end)
{
	return ((rand() % (end - start + 1)) + start);
}

int main()
{
	srand(time(NULL));
	Thread(Input);
	
	InitializeMonsterInfo();

	if (InitializeStage())
	{
		InitializePlayer();
		SetInputHandler(PlayerMove);
		Thread(ProcessObject);
		Thread(Render);
	}
	while (1)
	{

	}
}