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
		printf("\"%s\"파일을 찾을 수 없습니다.", name);
		fputs("파일 열기 에러!", stderr);
	}
	fseek(file, DATA_WIDTH, SEEK_SET);// 처음부터 가로길이를 나타내는 곳까지 이동
	width = fgetc(file); // 가로길이 대입
	fseek(file, DATA_HEIGHT, SEEK_SET);// 처음부터 세로길이를 나타내는 곳까지 이동
	height = fgetc(file); // 세로길이 대입
	image = (char**)malloc(sizeof(char) * width * height);
	fseek(file, DATA_START, SEEK_SET);
	// (w & 1)? (w>>1)+1:w>>1;//홀수라면 나누고 나머지 반쪽을 위해 +1,짝수라면 나누기
	padding = (4 - (((width & 1) ? (width >> 1) + 1 : width >> 1) % 4)) % 4;

	// 파일의 끝까지 ch에 데이터 읽어오기
	for (int x = 0, y = height - 1; (data = fgetc(file)) != EOF;)
	{
		// ch에 두 개의 문자로써 불러들이기 때문에 한번에 두번 처리해야된다.FF
		if (x < width) // 진행된 x가 가로길이보다 짧을때
		{
			image[x][y] = data >> 4; // 16진수에서의 첫번째자리문자를 대입
			x++;
			if (x < width)
			{
				image[x][y] = data % 16; // ch - (ch >> 4) * 16; // 두번째자리 문자를 대입
				x++;
			}
		}
		// 가로 값 전부 처리했을때
		if (x >= width)
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
}