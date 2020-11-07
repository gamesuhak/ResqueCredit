#include <string.h> // memset
#include <stdlib.h> // malloc
#include "Image.h"

Bitmap NewBitmap(int width, int height)
{
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
	return bitmap;
} // 참고 : https://codeng.tistory.com/8

// 이미지를 가로와 세로 개수로 나누어 반환하는 함수
Image** DivideBitmap(Image* image, int column, int rows)
{
	int width = image->width / column;
	int height = image->height / rows;
	Image** images = NULL;
	if (images == NULL) { printf("DivideBitmap\n"); return NULL; }
	images = (Image**)malloc(sizeof(Image*) * column * rows);
	for (int x = 0; x < column; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			images[x][y].bitmap = NewBitmap(width, height);
			for (int pixelX = 0; pixelX < width; pixelX++)
			{
				for (int pixelY = 0; pixelY < height; pixelY++)
				{
					images[x][y].bitmap[pixelX][pixelY] = image->bitmap[pixelX + width * x][pixelY + height * y];
				}
			}
		}
	}
	return images;
}

void DestroyBitmap(Bitmap bitmap)
{
	free(bitmap[0]);
	free(bitmap);
}