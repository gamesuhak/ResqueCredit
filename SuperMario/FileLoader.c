#include "FileLoader.h"

#include "Bool.h"
#include <stdio.h>
#include <stdlib.h> // malloc 사용
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
	//printf("\"%s\"파일을 로드 중...\n", name);
	if ((file = fopen(names, "rb")) == NULL)
	{
		printf("\"%s\"파일을 찾을 수 없습니다.", name);
		fputs("파일 열기 에러!", stderr);
	}
	fseek(file, DATA_WIDTH, SEEK_SET); // 처음부터 가로길이를 나타내는 곳까지 이동
	image->width = fgetc(file); // 가로길이 대입
	fseek(file, DATA_HEIGHT, SEEK_SET); // 처음부터 세로길이를 나타내는 곳까지 이동
	image->height = fgetc(file); // 세로길이 대입
	bitmap = NewBitmap(image->width, image->height);
	fseek(file, DATA_START, SEEK_SET);
	// (w & 1)? (w>>1)+1:w>>1;//홀수라면 나누고 나머지 반쪽을 위해 +1,짝수라면 나누기
	padding = (4 - (((image->width & 1) ? (image->width >> 1) + 1 : image->width >> 1) % 4)) % 4;

	// 파일의 끝까지 ch에 데이터 읽어오기
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
			(bitmap[x][y] == transparent) ? bitmap[x][y] = COLOR_TRANSPARENT : 0; // 해당 색상이 인자로 받은 배경색과 일치하면 COLOR_TRANSPARENT를 대입
		}
	}
	image->bitmap = bitmap;
	return image;
}