#include "Animator.h"
#include <stdlib.h> // NULL
#include "Image.h" // Image
#include "State.h" // State

extern Image** Sprites; // Image.c

// Sprite의 인덱스를 인자로 받아 애니메이터를 생성하는 메소드
// index = 초기 스프라이트의 번호, directionCount = 방향의 개수, frameTime = 한 스프라이트당 재생되는 시간
// frameCount = 상태별 프레임 개수 배열 포인터
Animator* NewAnimator(int index, int stateCount, int directionCount, int frameTime, int* frameCount)
{
	Animator* animator = (Animator*)malloc(sizeof(Animator));
	if (animator == NULL) { return NULL; }

	animator->frameTime = frameTime;
	animator->time = 0;
	animator->state = 0;
	animator->stateCount = stateCount;
	animator->animation = (Animation**)malloc(sizeof(Animation*) * stateCount);
	if (animator->animation == NULL) { return NULL; }

	// 상태의 개수만큼 반복
	for (int state = 0; state < stateCount; state++)
	{
		// 새 애니메이션을 생성하고 애니메이터의 애니메이션 배열에 연결
		animator->animation[state] = NewAnimation(index, directionCount, frameCount[state]);
		index += directionCount * frameCount[state];
	}
	return animator;
}

Animation* NewAnimation(int index, int directionCount, int frameCount)
{
	Animation* animation = (Animation*)malloc(sizeof(Animation));
	if (animation == NULL) { return NULL; }

	animation->frameCount = frameCount;
	animation->directionCount = directionCount;
	animation->clips = NewArray(frameCount, directionCount);
	for (int y = 0; y < directionCount; y++)
	{
		for (int x = 0; x < frameCount; x++)
		{
			animation->clips[x][y] = index + (y * frameCount) + x;
		}
	}
	return animation;
}