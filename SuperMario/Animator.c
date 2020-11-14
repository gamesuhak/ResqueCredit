#include "Animator.h"
#include <stdlib.h> // NULL
#include "Image.h" // Image
#include "State.h" // State

extern Image** Sprites; // Image.c

// Sprite�� �ε����� ���ڷ� �޾� �ִϸ����͸� �����ϴ� �޼ҵ�
// index = �ʱ� ��������Ʈ�� ��ȣ, directionCount = ������ ����, frameTime = �� ��������Ʈ�� ����Ǵ� �ð�
// frameCount = ���º� ������ ���� �迭 ������
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

	// ������ ������ŭ �ݺ�
	for (int state = 0; state < stateCount; state++)
	{
		// �� �ִϸ��̼��� �����ϰ� �ִϸ������� �ִϸ��̼� �迭�� ����
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