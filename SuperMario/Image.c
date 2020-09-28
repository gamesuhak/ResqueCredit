#include <string.h> // memset
#include <stdlib.h> // malloc
#include "Image.h"

Bitmap NewBitmap(int width, int height)
{
	//printf("NewBitmap\n");
	Bitmap bitmap = NULL;
	bitmap = (Bitmap)malloc(sizeof(char*) * width);
	if (bitmap == NULL) { printf("CreateBitmap2\n"); return NULL; }
	bitmap[0] = (char*)malloc(sizeof(char) * width * height);
	if (bitmap[0] == NULL) { printf("CreateBitmap3\n"); return NULL; }
	for (int i = 1; i < width; i++)
	{
		bitmap[i] = bitmap[i - 1] + height;
		if (bitmap[i] == NULL) { printf("CreateBitmap : %d\n", i); return NULL; }
	}
	
	memset(bitmap[0], COLOR_TRANSPARENT, sizeof(char) * width * height);
	//printf("width : %d, height : %d\n", width, height);
	
	//TestBitmap(width, height, bitmap);

	return bitmap;
	// 참고 : https://codeng.tistory.com/8
}

// 이미지를 가로와 세로 개수로 나누어 반환하는 함수
void DivideBitmap(Image* image, int column, int rows)
{
	int width = image->width / column;
	int height = image->height / rows;
	Image** list = NULL;
	list = (Image**)malloc(sizeof(Image*) * column * rows);
	for (int x = 0; x < column; x++)
	{
		for (int y = 0; y < column; y++)
		{
			NewBitmap(width, height);
		}
	}
}

void DestroyBitmap(Bitmap bitmap)
{
	free(bitmap[0]);
	free(bitmap);
}