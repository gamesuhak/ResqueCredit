#include "FileLoader.h"

#include "Bool.h"
#include <stdio.h>
#include <stdlib.h> // malloc ���
#include <string.h>

enum Color
{
	COLOR_TRANSPARENT = -1, COLOR_BLACK = 0, COLOR_DARKBLUE, COLOR_DARKGREEN, COLOR_DARKSKY, COLOR_DARKRED, COLOR_DARKPINK, COLOR_DARKYELLOW, COLOR_DARKWHITE,
	COLOR_GRAY, COLOR_BLUE, COLOR_GREEN, COLOR_SKY, COLOR_RED, COLOR_PINK, COLOR_YELLOW, COLOR_WHITE
};

struct Image
{
	int id;
	int width;
	int height;
	int pivotx;
	int pivoty;
	Bitmap bitmap;
};

Image* LoadBitmapFile(char* name, Color transparent)
{
	//printf("LoadBitmapFile\n");
	Image* image = (Image*)malloc(sizeof(Image));
	Bitmap bitmap;
	FILE* file = NULL;
	int data;
	char padding;
	char names[50] = "Image/";
	strcat(names, name);
	strcat(names, ".bmp");
	//printf("\"%s\"������ �ε� ��...\n", name);
	if ((file = fopen(names, "rb")) == NULL)
	{
		printf("\"%s\"������ ã�� �� �����ϴ�.", name);
		fputs("���� ���� ����!", stderr);
	}
	fseek(file, DATA_WIDTH, SEEK_SET); // ó������ ���α��̸� ��Ÿ���� ������ �̵�
	image->width = fgetc(file); // ���α��� ����
	fseek(file, DATA_HEIGHT, SEEK_SET); // ó������ ���α��̸� ��Ÿ���� ������ �̵�
	image->height = fgetc(file); // ���α��� ����
	bitmap = NewBitmap(image->width, image->height);
	fseek(file, DATA_START, SEEK_SET);
	// (w & 1)? (w>>1)+1:w>>1;//Ȧ����� ������ ������ ������ ���� +1,¦����� ������
	padding = (4 - (((image->width & 1) ? (image->width >> 1) + 1 : image->width >> 1) % 4)) % 4;

	// ������ ������ ch�� ������ �о����
	for (int y = image->height - 1; y >= 0 ;y--)
	{
		for (char x = 0; x < image->width && (data = fgetc(file)) != EOF; x++)
		{
			bitmap[x][y] = data >> 4;

			if (bitmap[x][y] == COLOR_DARKBLUE) { bitmap[x][y] = COLOR_DARKRED; }
			else if (bitmap[x][y] == COLOR_DARKSKY) { bitmap[x][y] = COLOR_DARKYELLOW; }
			else if (bitmap[x][y] == COLOR_DARKRED) { bitmap[x][y] = COLOR_DARKBLUE; }
			else if (bitmap[x][y] == COLOR_DARKYELLOW) { bitmap[x][y] = COLOR_DARKSKY; }
			else if (bitmap[x][y] == COLOR_DARKWHITE) { bitmap[x][y] = COLOR_GRAY; }
			else if (bitmap[x][y] == COLOR_GRAY) { bitmap[x][y] = COLOR_DARKWHITE; }
			else if (bitmap[x][y] == COLOR_BLUE) { bitmap[x][y] = COLOR_RED; }
			else if (bitmap[x][y] == COLOR_SKY) { bitmap[x][y] = COLOR_YELLOW; }
			else if (bitmap[x][y] == COLOR_RED) { bitmap[x][y] = COLOR_BLUE; }
			else if (bitmap[x][y] == COLOR_YELLOW) { bitmap[x][y] = COLOR_SKY; }
			
			if (x >= image->width)
			{
				break;
			}
			bitmap[++x][y] = data % 16;

			if (bitmap[x][y] == COLOR_DARKBLUE) { bitmap[x][y] = COLOR_DARKRED; }
			else if (bitmap[x][y] == COLOR_DARKSKY) { bitmap[x][y] = COLOR_DARKYELLOW; }
			else if (bitmap[x][y] == COLOR_DARKRED) { bitmap[x][y] = COLOR_DARKBLUE; }
			else if (bitmap[x][y] == COLOR_DARKYELLOW) { bitmap[x][y] = COLOR_DARKSKY; }
			else if (bitmap[x][y] == COLOR_DARKWHITE) { bitmap[x][y] = COLOR_GRAY; }
			else if (bitmap[x][y] == COLOR_GRAY) { bitmap[x][y] = COLOR_DARKWHITE; }
			else if (bitmap[x][y] == COLOR_BLUE) { bitmap[x][y] = COLOR_RED; }
			else if (bitmap[x][y] == COLOR_SKY) { bitmap[x][y] = COLOR_YELLOW; }
			else if (bitmap[x][y] == COLOR_RED) { bitmap[x][y] = COLOR_BLUE; }
			else if (bitmap[x][y] == COLOR_YELLOW) { bitmap[x][y] = COLOR_SKY; }
		}
		fseek(file, padding, SEEK_CUR);
	}
	
	for (char y = 0; y < image->height; y++)
	{
		for (char x = 0; x < image->width; x++)
		{
			(bitmap[x][y] == transparent) ? bitmap[x][y] = COLOR_TRANSPARENT : 0; // �ش� ������ ���ڷ� ���� ������ ��ġ�ϸ� COLOR_TRANSPARENT�� ����
		}
	}
	image->bitmap = bitmap;
	return image;
}