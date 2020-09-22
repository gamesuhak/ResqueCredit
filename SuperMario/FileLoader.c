#include "FileLoader.h"

#include <stdio.h>
#include <stdlib.h> // malloc ���
#include <string.h>

#define DATA_WIDTH		18
#define DATA_HEIGHT		22
#define DATA_START		118

enum Color
{
	COLOR_TRANSPARENT = -1, COLOR_BLACK, COLOR_DARKRED, COLOR_DARKGREEN, COLOR_DARKYELLOW, COLOR_DARKBLUE, COLOR_DARKPINK, COLOR_DARKSKY, COLOR_GRAY,
	COLOR_DARKWHITE, COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE, COLOR_PINK, COLOR_SKY, COLOR_WHITE
};

struct Image
{
	int id;
	int width;
	int height;
	Bitmap bitmap;
};

Image* LoadBitmapFile(char* name, Color transparent)
{
	printf("LoadBitmapFile\n");
	Image* image = (Image*)malloc(sizeof(Image));
	Bitmap bitmap;
	FILE* file = NULL;
	int data;
	char padding, x, y;
	char names[50] = "Image/";
	strcat(names, name);
	strcat(names, ".bmp");
	printf("\"%s\"������ �ε� ��...\n", name);
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
	for (x = 0, y = image->height - 1; (data = fgetc(file)) != EOF;)
	{
		// ch�� �� ���� ���ڷν� �ҷ����̱� ������ �ѹ��� �ι� ó���ؾߵȴ�.FF
		if (x < image->width) // ����� x�� ���α��̺��� ª����
		{
			bitmap[x][y] = data >> 4; // 16���������� ù��°�ڸ����ڸ� ����
			if (bitmap[x][y] < 0)
			{
				//printf("%d, %d�� �������Ծ�\n", x, y, bitmap[x][y]);
			}
			x++;
			if (x < image->width)
			{
				bitmap[x][y] = data % 16; // ch - (ch >> 4) * 16; // �ι�°�ڸ� ���ڸ� ����
				//bitmap[x][y] = data - (data >> 4) * 16;
				x++;
			}
		}
		// ���� �� ���� ó��������
		if (x >= image->width)
		{
			// y�� ���ҽ�ų�� ������ ����
			if (y > 0)
			{
				y--;
			}
			// y�� 0�̸� for�� ����
			else
			{
				break;
			}
			// ���� �ʱ�ȭ
			x = 0;
			fseek(file, padding, SEEK_CUR); // �е��� ũ�⸸ŭ Ŀ���� �̵���Ų��
		}
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