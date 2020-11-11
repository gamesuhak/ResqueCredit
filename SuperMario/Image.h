#pragma once
#include "Color.h"
#include "Coordination.h"
typedef char** Bitmap;
typedef struct Image Image;

struct Image
{
	int id;
	int width;
	int height;
	Coordination pivot;
	Bitmap bitmap;
};

Bitmap NewBitmap(int width, int height);
void DestroyBitmap(Bitmap bitmap);
Image* NewImage(int width, int height);
Image** SliceImage(Image* image, int column, int row);
void AddImage(int x, int y, Image* image, Image* target);