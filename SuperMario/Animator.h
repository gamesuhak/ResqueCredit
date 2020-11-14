#pragma once
typedef struct Animator Animator;
typedef struct Animation Animation;

typedef char** AnimationClip;

struct Animation
{
	int frameCount;
	int directionCount;
	AnimationClip clips;
};

struct Animator
{
	int frameTime; // 다음 프레임으로 넘어가는데 걸리는 시간
	int time; // 현재 재생 시간
	char state; // 현재 애니메이터의 상태
	int stateCount; // 상태 개수
	Animation** animation; // 애니메이션
};

Animator* NewAnimator(int index, int stateCount, int directionCount, int frameTime, int* frameCount);
Animation* NewAnimation(int index, int directionCount, int frameCount);