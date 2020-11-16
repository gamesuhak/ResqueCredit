#pragma once
#include "Color.h"
#include "Coordination.h"
#include <stdlib.h> // NULL

typedef char** Bitmap;
typedef char** Array;
typedef enum Pivot { PIVOT_LEFTUP = 0, PIVOT_MIDDLE } Pivot;
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
void SetArray(Array array, int width, int height, int data);
void ReleaseArray(Array array);
Array DuplicateArray(Array array, int width, int height);

// 이미지 메소드
Image* NewImage(int width, int height);
Image* DuplicateImage(Image* image);
void ReleaseImage(Image* image);
Image** SliceImage(Image* image, int column, int row);
void AddImage(int x, int y, Image* image, Image* target);
void FillImage(Image* image, Color color);