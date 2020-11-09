#include <string.h> // memset
#include <stdlib.h> // malloc
#include "Image.h"

Bitmap NewBitmap(int width, int height)
{
	Bitmap tileData = NULL;
	tileData = (Bitmap)malloc(sizeof(char*) * width);
	if (tileData == NULL) { printf("CreateBitmap2\n"); return NULL; }
	tileData[0] = (char*)malloc(sizeof(char) * width * height);
	if (tileData[0] == NULL) { printf("CreateBitmap3\n"); return NULL; }
	for (int i = 1; i < width; i++)
	{
		tileData[i] = tileData[i - 1] + height;
		if (tileData[i] == NULL) { printf("CreateBitmap : %d\n", i); return NULL; }
	}
	
	memset(tileData[0], COLOR_TRANSPARENT, sizeof(char) * width * height);
	return tileData;
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
			images[x][y].tileData = NewBitmap(width, height);
			for (int pixelX = 0; pixelX < width; pixelX++)
			{
				for (int pixelY = 0; pixelY < height; pixelY++)
				{
					images[x][y].tileData[pixelX][pixelY] = image->tileData[pixelX + width * x][pixelY + height * y];
				}
			}
		}
	}
	return images;
}

void DestroyBitmap(Bitmap tileData)
{
	free(tileData[0]);
	free(tileData);
}