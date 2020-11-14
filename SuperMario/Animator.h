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
	int frameTime; // ���� ���������� �Ѿ�µ� �ɸ��� �ð�
	int time; // ���� ��� �ð�
	char state; // ���� �ִϸ������� ����
	int stateCount; // ���� ����
	Animation** animation; // �ִϸ��̼�
};

Animator* NewAnimator(int index, int stateCount, int directionCount, int frameTime, int* frameCount);
Animation* NewAnimation(int index, int directionCount, int frameCount);