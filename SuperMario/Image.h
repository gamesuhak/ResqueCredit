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

// 비트맵 메소드
Bitmap NewBitmap(int width, int height);
void ReleaseBitmap(Bitmap bitmap);

// 이미지 메소드
Image* NewImage(int width, int height);
void ReleaseImage(Image* image);
Image** SliceImage(Image* image, int column, int row);
void AddImage(int x, int y, Image* image, Image* target);