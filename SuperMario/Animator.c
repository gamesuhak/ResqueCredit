#include "Animator.h"
#include <stdlib.h> // NULL
#include "Image.h" // Image
#include "State.h" // State

extern Image** Sprite;

// Sprite의 인덱스를 인자로 받아 애니메이터를 생성하는 메소드
Animator* NewAnimator(int index, int stateCount, int directionCount, int frameCount)
{
	Animator* animator = (Animator*)malloc(sizeof(Animator));
	if (animator == NULL) { return NULL; }

	char*** spriteseses = (char***)malloc(sizeof(char**) * stateCount);
	if (spriteseses == NULL) { return NULL; }

	for (int state = 0; state < stateCount; state++)
	{
		char** spriteses = (char**)malloc(sizeof(char*) * directionCount);
		if (spriteses == NULL) { return NULL; }
		for (int direction = 0; direction < directionCount; direction++)
		{
			char* sprites = (char*)malloc(sizeof(char) * frameCount);
			if (sprites == NULL) { return NULL; }
			for (int frame = 0; frame < frameCount; frame++)
			{
				sprites[frame] = index++;
			}
			spriteses[direction] = sprites;
		}
		spriteseses[state] = spriteses;
	}

	return animator;
}

void CreateAnimator(int index)
{
	char*** sprites[STATE_COUNT];

	sprites[STATE_IDLE] = SetIdle(index, 4, 1);
	//Animator* animator = NewAnimator();
}

char** SetIdle(int index, int directionCount, int frameCount)
{
	char** node = NewArray(frameCount, directionCount);
	for (int y = 0; y < directionCount; y++)
	{
		for (int x = 0; x < frameCount; x++)
		{
			node[x][y] = index + (y * frameCount) + x;
		}
	}
	return node;
}

char** SetWalk(int index, int directionCount, int frameCount)
{
	char** node = NewArray(frameCount, directionCount);
	for (int y = 0; y < directionCount; y++)
	{
		for (int x = 0; x < frameCount; x++)
		{
			node[x][y] = index + (y * frameCount) + x;
		}
	}
	return node;
}