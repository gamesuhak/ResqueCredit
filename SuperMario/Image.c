#include <stdlib.h>
typedef char** Bitmap;

Bitmap AllocateBitmap(int width, int height)
{
	Bitmap bitmap = (Bitmap)malloc(sizeof(char*) * width);
	bitmap[0] = (char*)malloc(sizeof(char) * height);
	for (int i = 1; i < height; i++)
	{
		bitmap[i] = bitmap[i - 1] + height;
	}
	// ���� : https://codeng.tistory.com/8
}

Bitmap CreateBitmap(int width, int height)
{
	Bitmap bitmap = (Bitmap)malloc(sizeof(char) * height * width);
	return bitmap;
	// ���� : https://codeng.tistory.com/8
}