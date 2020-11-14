#include "Animator.h"
#include <stdlib.h> // NULL
#include "Image.h" // Image

extern Image** Sprite;

Animator* NewAnimator(int index)
{
	Animator* animator = (Animator*)malloc(sizeof(Animator));
	if (animator == NULL) { return NULL; }
	return animator;
}

void CreateAnimator()
{

}