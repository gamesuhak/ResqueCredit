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

void DestroyBitmap(Bitmap bitmap)
{
	free(bitmap[0]);
	free(bitmap);
}

Image* NewImage(int width, int height)
{
	Image* image = (Image*)malloc(sizeof(Image));
	if (image == NULL) { return NULL; }

	image->id = 0;
	image->pivotx = 0;
	image->pivoty = 0;
	return image;
}

// 이미지를 가로와 세로 개수로 나누어 반환하는 함수
Image** SliceImage(Image* image, int column, int row)
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
void AddImage(int x, int y, Image* image, Bitmap target)
{
	for (int posx = 0; posx < image->width; posx++)
	{
		for (int posy = 0; posy < image->height; posy++)
		{
			if ((image->bitmap[posx][posy] < 0) || ((posx + x - image->pivotx < 0) || (posy + y - image->pivoty < 0)))
			{
				continue;
			}
			target[posx + x - image->pivotx][posy + y - image->pivoty] = image->bitmap[posx][posy];
		}
	}
}

// 이미지를 이미지에 그리는 함수
void AddImage2(int x, int y, Image* image, Image* target)
{
	for (int posx = 0; posx < image->width; posx++)
	{
		for (int posy = 0; posy < image->height; posy++)
		{
			if ((image->bitmap[posx][posy] < 0) || // 현재 가르키고있는 색상이 없을 때
				((posx + x - image->pivotx < 0) || (posy + y - image->pivoty < 0)) ||
				((posx + x - image->pivotx >= target->width) || (posy + y - image->pivoty > target->height))) {
				continue;
			}
			target->bitmap[posx + x - image->pivotx][posy + y - image->pivoty] = image->bitmap[posx][posy];
		}
	}
}