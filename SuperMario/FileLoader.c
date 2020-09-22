#include "FileLoader.h"

#include <stdio.h>
#include <stdlib.h> // malloc 사용
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
	printf("\"%s\"파일을 로드 중...\n", name);
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
	for (x = 0, y = image->height - 1; (data = fgetc(file)) != EOF;)
	{
		// ch에 두 개의 문자로써 불러들이기 때문에 한번에 두번 처리해야된다.FF
		if (x < image->width) // 진행된 x가 가로길이보다 짧을때
		{
			bitmap[x][y] = data >> 4; // 16진수에서의 첫번째자리문자를 대입
			if (bitmap[x][y] < 0)
			{
				//printf("%d, %d에 음수나왔어\n", x, y, bitmap[x][y]);
			}
			x++;
			if (x < image->width)
			{
				bitmap[x][y] = data % 16; // ch - (ch >> 4) * 16; // 두번째자리 문자를 대입
				//bitmap[x][y] = data - (data >> 4) * 16;
				x++;
			}
		}
		// 가로 값 전부 처리했을때
		if (x >= image->width)
		{
			// y값 감소시킬수 있으면 감소
			if (y > 0)
			{
				y--;
			}
			// y가 0이면 for문 종료
			else
			{
				break;
			}
			// 가로 초기화
			x = 0;
			fseek(file, padding, SEEK_CUR); // 패딩의 크기만큼 커서를 이동시킨다
		}
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