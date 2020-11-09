#pragma once

typedef struct Animator Animator;

struct Animator
{
	char* name;
	int currentFrame;

	int* spriteNumber;
};