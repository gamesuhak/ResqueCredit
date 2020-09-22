#include <string.h> // memset
#include <stdlib.h> // malloc
#include "Image.h"

enum Color
{
	COLOR_TRANSPARENT = -1, COLOR_BLACK, COLOR_DARKRED, COLOR_DARKGREEN, COLOR_DARKYELLOW, COLOR_DARKBLUE, COLOR_DARKPINK, COLOR_DARKSKY, COLOR_GRAY,
	COLOR_DARKWHITE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_PINK, COLOR_SKY, COLOR_WHITE
};

void TestBitmap(int width, int height, Bitmap bitmap);

Bitmap NewBitmap(int width, int height)
{
	printf("NewBitmap\n");
	Bitmap bitmap = NULL;
	bitmap = (Bitmap)malloc(sizeof(char*) * width);
	if (bitmap == NULL) { printf("CreateBitmap2\n"); return NULL; }
	bitmap[0] = (char*)malloc(sizeof(char) * width * height);
	if (bitmap[0] == NULL) { printf("CreateBitmap3\n"); return NULL; }

	for (char i = 1; i < width; i++)
	{
		bitmap[i] = bitmap[i - 1] + height;
	}

	memset(bitmap[0], COLOR_TRANSPARENT, sizeof(char) * width * height);
	printf("width : %d, height : %d\n", width, height);
	
	//TestBitmap(width, height, bitmap);

	return bitmap;
	// Âü°í : https://codeng.tistory.com/8
}

void TestBitmap(int width, int height, Bitmap bitmap)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			printf("%d,", bitmap[x][y]);
		}
		printf("\n");
	}
	
}

void DestroyBitmap(Bitmap bitmap)
{
	free(bitmap[0]);
	free(bitmap);
}