#include <string.h> // memset
#include <stdlib.h> // malloc
#include "Image.h"

Bitmap NewBitmap(int width, int height)
{
	Bitmap bitmap = NULL;
	bitmap = (Bitmap)malloc(sizeof(char*) * width);
	if (bitmap == NULL) { printf("NewBitmap2\n"); return NULL; }
	bitmap[0] = (char*)malloc(sizeof(char) * width * height);
	if (bitmap[0] == NULL) { printf("NewBitmap3\n"); return NULL; }
	for (int i = 1; i < width; i++)
	{
		bitmap[i] = bitmap[i - 1] + height;
		if (bitmap[i] == NULL) { printf("NewBitmap : %d\n", i); return NULL; }
	}
	
	memset(bitmap[0], COLOR_TRANSPARENT, sizeof(char) * width * height);
	return bitmap;
} // 참고 : https://codeng.tistory.com/8

void ReleaseBitmap(Bitmap bitmap)
{
	free(bitmap[0]);
	free(bitmap);
}

Image* NewImage(int width, int height)
{
	Image* image = (Image*)malloc(sizeof(Image));
	if (image == NULL) { return NULL; }

	image->id = 0;
	image->pivot.x = 0;
	image->pivot.y = 0;
	image->width = width;
	image->height = height;
	image->bitmap = NewBitmap(width, height);
	return image;
}

void ReleaseImage(Image* image)
{
	ReleaseBitmap(image->bitmap);
	free(image);
}

// 이미지를 가로와 세로 개수로 나누어 반환하는 함수
Image** SliceImage(Image* image, int column, int row)
{
	int width = image->width / column;
	int height = image->height / row;
	Image** images = (Image**)malloc(sizeof(Image*) * column * row);
	if (images == NULL) { printf("SliceImage\n"); return NULL; }
	
	for (int y = 0; y < row; y++)
	{
		for (int x = 0; x < column; x++)
		{
			images[y * row + x] = NewImage(width, height);
			for (int pixelX = 0; pixelX < width; pixelX++)
			{
				for (int pixelY = 0; pixelY < height; pixelY++)
				{
					images[y * row + x]->bitmap[pixelX][pixelY] = image->bitmap[pixelX + width * x][pixelY + height * y];
				}
			}
		}
	}
	return images;
}

Image** SliceImagePixel(Image* image, int column, int row)
{
	int width = image->width / column;
	int height = image->height / row;
	Image** images = NULL;
	if (images == NULL) { printf("SliceImage\n"); return NULL; }
	images = (Image**)malloc(sizeof(Image*) * column * row);
	for (int x = 0; x < column; x++)
	{
		for (int y = 0; y < row; y++)
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

// 이미지를 이미지에 그리는 함수
void AddImage(int x, int y, Image* image, Image* target)
{
	for (int posx = 0; posx < image->width; posx++)
	{
		for (int posy = 0; posy < image->height; posy++)
		{
			if ((image->bitmap[posx][posy] < 0) || // 현재 가르키고있는 색상이 없을 때
				((posx + x - image->pivot.x < 0) || (posy + y - image->pivot.y < 0)) ||
				((posx + x - image->pivot.x >= target->width) || (posy + y - image->pivot.y > target->height))) {
				continue;
			}
			target->bitmap[posx + x - image->pivot.x][posy + y - image->pivot.y] = image->bitmap[posx][posy];
		}
	}
}