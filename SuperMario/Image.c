#include <string.h> // memset
#include <stdlib.h> // malloc
#include "Image.h"

Array NewArray(int width, int height)
{
	Array array = NULL;
	array = (Array)malloc(sizeof(char*) * width);
	if (array == NULL) { printf("NewBitmap2\n"); return NULL; }
	array[0] = (char*)malloc(sizeof(char) * width * height);
	if (array[0] == NULL) { printf("NewBitmap3\n"); return NULL; }
	for (int i = 1; i < width; i++)
	{
		array[i] = array[i - 1] + height;
		if (array[i] == NULL) { printf("NewArray : %d\n", i); return NULL; }
	}
	
	memset(array[0], COLOR_TRANSPARENT, sizeof(char) * width * height);
	return array;
} // 참고 : https://codeng.tistory.com/8

void SetArray(Array array, int width, int height, int data)
{
	memset(array[0], data, sizeof(char) * width * height);
}

void ReleaseArray(Array array)
{
	free(array[0]);
	free(array);
}

Array DuplicateArray(Array array, int width, int height)
{
	Array data = NewArray(width, height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			data[x][y] = array[x][y];
		}
	}
	return data;
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
	image->bitmap = NewArray(width, height);
	return image;
}

void ReleaseImage(Image* image)
{
	ReleaseArray(image->bitmap);
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
			images[y * (row - 1) + x] = NewImage(width, height);
			for (int pixelX = 0; pixelX < width; pixelX++)
			{
				for (int pixelY = 0; pixelY < height; pixelY++)
				{
					images[y * (row - 1) + x]->bitmap[pixelX][pixelY] = image->bitmap[pixelX + width * x][pixelY + height * y];
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
			images[x][y].bitmap = NewArray(width, height);
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

void FillImage(Image* image, Color color)
{
	memset(image->bitmap[0], color, sizeof(char) * image->width * image->height);
}