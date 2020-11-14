#pragma once
typedef struct Animator Animator;

struct Animator
{
	char currentFrame;
	char state;
	char asd;
};

Animator* NewAnimator(int index);

void CreateAnimator();
