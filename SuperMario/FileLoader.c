#include "FileLoader.h"
#define DATA_WIDTH		18
#define DATA_HEIGHT		22
#define DATA_START		118

enum Color
{
	COLOR_BLACK = 0, COLOR_DARKBLUE, COLOR_DARKGREEN, COLOR_DARKSKY, COLOR_DARKRED, COLOR_DARKPINK, COLOR_DARKYELLOW, COLOR_DARKWHITE,
	COLOR_GRAY, COLOR_BLUE, COLOR_GREEN, COLOR_SKY, COLOR_RED, COLOR_PINK, COLOR_YELLOW, COLOR_WHITE
};

struct Image
{
	int id;
	int width;
	int height;
	char** data;
};

char** LoadImage(char* name, Color transparent)
{
	char** image;
	FILE* file = NULL;
	char width, height, padding, data;
	char names[50] = "Image/";
	strcat(names, name);
	strcat(names, ".bmp");

	if ((file = fopen(names, "rb")) == NULL)
	{
		printf("\"%s\"������ ã�� �� �����ϴ�.", name);
		fputs("���� ���� ����!", stderr);
	}
	fseek(file, DATA_WIDTH, SEEK_SET);// ó������ ���α��̸� ��Ÿ���� ������ �̵�
	width = fgetc(file); // ���α��� ����
	fseek(file, DATA_HEIGHT, SEEK_SET);// ó������ ���α��̸� ��Ÿ���� ������ �̵�
	height = fgetc(file); // ���α��� ����
	image = (char**)malloc(sizeof(char) * width * height);
	fseek(file, DATA_START, SEEK_SET);
	// (w & 1)? (w>>1)+1:w>>1;//Ȧ����� ������ ������ ������ ���� +1,¦����� ������
	padding = (4 - (((width & 1) ? (width >> 1) + 1 : width >> 1) % 4)) % 4;

	// ������ ������ ch�� ������ �о����
	for (int x = 0, y = height - 1; (data = fgetc(file)) != EOF;)
	{
		// ch�� �� ���� ���ڷν� �ҷ����̱� ������ �ѹ��� �ι� ó���ؾߵȴ�.FF
		if (x < width) // ����� x�� ���α��̺��� ª����
		{
			image[x][y] = data >> 4; // 16���������� ù��°�ڸ����ڸ� ����
			x++;
			if (x < width)
			{
				image[x][y] = data % 16; // ch - (ch >> 4) * 16; // �ι�°�ڸ� ���ڸ� ����
				x++;
			}
		}
		// ���� �� ���� ó��������
		if (x >= width)
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
}