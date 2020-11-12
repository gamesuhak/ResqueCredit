#pragma once
#include "Color.h"
#include "Coordination.h"
typedef char** Bitmap;
typedef char** Array;
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
Bitmap NewArray(int width, int height);
void ReleaseArray(Array array);
Array DuplicateArray(Array array, int width, int height);

// 이미지 메소드
Image* NewImage(int width, int height);
void ReleaseImage(Image* image);
Image** SliceImage(Image* image, int column, int row);
void AddImage(int x, int y, Image* image, Image* target);