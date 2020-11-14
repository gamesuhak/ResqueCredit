#pragma once
typedef struct Animator Animator;

struct Animator
{
	char currentFrame;
	char maxFrame;
	char state;
	char*** sprites;
};

Animator* NewAnimator(int index, int stateCount, int directionCount, int frameCount);

void CreateAnimator();