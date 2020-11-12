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

// ��Ʈ�� �޼ҵ�
Bitmap NewArray(int width, int height);
void ReleaseArray(Array array);
Array DuplicateArray(Array array, int width, int height);

// �̹��� �޼ҵ�
Image* NewImage(int width, int height);
void ReleaseImage(Image* image);
Image** SliceImage(Image* image, int column, int row);
void AddImage(int x, int y, Image* image, Image* target);