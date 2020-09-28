#pragma once
#include "Color.h"
typedef char** Bitmap;
typedef struct Image
{
	int id;
	int width;
	int height;
	int pivotx;
	int pivoty;
	Bitmap bitmap;
} Image;

Bitmap NewBitmap(int width, int height);