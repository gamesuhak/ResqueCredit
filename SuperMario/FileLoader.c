#include "FileLoader.h"

#include "Bool.h"
#include <stdio.h>
#include <stdlib.h> // malloc 사용
#include <string.h> // strcat strok 사용

extern int RoomInfoCount;
extern int MonsterInfoCount;

Image* LoadBitmapFile(char* name, Color transparent)
{
	Image* image;
	FILE* file = NULL;
	int data, width, height;
	char padding;
	char names[50] = "Image/";
	strcat(names, name);
	strcat(names, ".bmp");
	if ((file = fopen(names, "rb")) == NULL)
	{
		printf("\"%s\"파일을 찾을 수 없습니다.", name);
		fputs("파일 열기 에러!", stderr);
	}

	fseek(file, DATA_WIDTH, SEEK_SET); // 처음부터 가로길이를 나타내는 곳까지 이동
	width = fgetc(file); // 가로길이 대입
	fseek(file, DATA_HEIGHT, SEEK_SET); // 처음부터 세로길이를 나타내는 곳까지 이동
	height = fgetc(file); // 세로길이 대입
	image = NewImage(width, height);

	//bitmap = NewArray(image->width, image->height);
	fseek(file, DATA_START, SEEK_SET);
	// (w & 1)? (w>>1)+1:w>>1;//홀수라면 나누고 나머지 반쪽을 위해 +1,짝수라면 나누기
	padding = (4 - (((image->width & 1) ? (image->width >> 1) + 1 : image->width >> 1) % 4)) % 4;

	// 파일의 끝까지 ch에 데이터 읽어오기
	for (int y = image->height - 1; y >= 0 ;y--)
	{
		for (char x = 0; x < image->width && (data = fgetc(file)) != EOF; x++)
		{
			image->bitmap[x][y] = data >> 4;

			if (image->bitmap[x][y] == COLOR_DARKBLUE) { image->bitmap[x][y] = COLOR_DARKRED; }
			else if (image->bitmap[x][y] == COLOR_DARKSKY) { image->bitmap[x][y] = COLOR_DARKYELLOW; }
			else if (image->bitmap[x][y] == COLOR_DARKRED) { image->bitmap[x][y] = COLOR_DARKBLUE; }
			else if (image->bitmap[x][y] == COLOR_DARKYELLOW) { image->bitmap[x][y] = COLOR_DARKSKY; }
			else if (image->bitmap[x][y] == COLOR_DARKWHITE) { image->bitmap[x][y] = COLOR_GRAY; }
			else if (image->bitmap[x][y] == COLOR_GRAY) { image->bitmap[x][y] = COLOR_DARKWHITE; }
			else if (image->bitmap[x][y] == COLOR_BLUE) { image->bitmap[x][y] = COLOR_RED; }
			else if (image->bitmap[x][y] == COLOR_SKY) { image->bitmap[x][y] = COLOR_YELLOW; }
			else if (image->bitmap[x][y] == COLOR_RED) { image->bitmap[x][y] = COLOR_BLUE; }
			else if (image->bitmap[x][y] == COLOR_YELLOW) { image->bitmap[x][y] = COLOR_SKY; }
			
			if (x >= image->width)
			{
				break;
			}
			image->bitmap[++x][y] = data % 16;

			if (image->bitmap[x][y] == COLOR_DARKBLUE) { image->bitmap[x][y] = COLOR_DARKRED; }
			else if (image->bitmap[x][y] == COLOR_DARKSKY) { image->bitmap[x][y] = COLOR_DARKYELLOW; }
			else if (image->bitmap[x][y] == COLOR_DARKRED) { image->bitmap[x][y] = COLOR_DARKBLUE; }
			else if (image->bitmap[x][y] == COLOR_DARKYELLOW) { image->bitmap[x][y] = COLOR_DARKSKY; }
			else if (image->bitmap[x][y] == COLOR_DARKWHITE) { image->bitmap[x][y] = COLOR_GRAY; }
			else if (image->bitmap[x][y] == COLOR_GRAY) { image->bitmap[x][y] = COLOR_DARKWHITE; }
			else if (image->bitmap[x][y] == COLOR_BLUE) { image->bitmap[x][y] = COLOR_RED; }
			else if (image->bitmap[x][y] == COLOR_SKY) { image->bitmap[x][y] = COLOR_YELLOW; }
			else if (image->bitmap[x][y] == COLOR_RED) { image->bitmap[x][y] = COLOR_BLUE; }
			else if (image->bitmap[x][y] == COLOR_YELLOW) { image->bitmap[x][y] = COLOR_SKY; }
		}
		fseek(file, padding, SEEK_CUR);
	}
	
	for (char y = 0; y < image->height; y++)
	{
		for (char x = 0; x < image->width; x++)
		{
			(image->bitmap[x][y] == transparent) ? image->bitmap[x][y] = COLOR_TRANSPARENT : 0; // 해당 색상이 인자로 받은 배경색과 일치하면 COLOR_TRANSPARENT를 대입
		}
	}
	return image;
}

RoomInfo* LoadRoomFile(char* name)
{
	RoomInfo* room;	
	FILE* file;
	char names[50] = "Map/";
	strcat(names, name);
	strcat(names, ".txt");
	if ((file = fopen(names, "rt")) == NULL) { return NULL; }
	
	room = (Stage*)malloc(sizeof(Stage));
	if (room == NULL) { return NULL; }

	fscanf(file, "Type : %d\n", &room->type);
	room->width = 0;
	room->height = 0;
	room->percentage = 0;
	room->tile = NewArray(room->width, room->height);
	room->tag = NewArray(room->width, room->height);
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			//room->tile[x][y] = fgetc();
		}
	}
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			//room->tag[x][y] = fgetc();
		}
	}


	for (int i = 0; i < room->height; i++)
	{
		for (int j = 0; j < room->width; j++)
		{
			fscanf(file, "%d ", room->tile[i][j]);
		}
	}

	fclose(file);
}

MonsterInfo* LoadMonsterFile(char* name)
{
	FILE* file;
	char names[50] = "Monster/";
	strcat(names, name);
	strcat(names, ".txt");
	if ((file = fopen(names, "rb")) == NULL) { return NULL; }

	MonsterInfo* monsterInfo = (MonsterInfo*)malloc(sizeof(MonsterInfo));
	monsterInfo->id;
	monsterInfo->hp;
	monsterInfo->power;
	monsterInfo->speed;
	
	monsterInfo->object.layer = 1;

	monsterInfo->object.position.x = 1;
	monsterInfo->object.position.y = 1;

	monsterInfo->object.direction.x = 1;
	monsterInfo->object.direction.y = 1;

	monsterInfo->object.collider.pivot.x = 0;
	monsterInfo->object.collider.pivot.y = 0;
	monsterInfo->object.collider.size.x = 0;
	monsterInfo->object.collider.size.y = 0;
	
	return monsterInfo;
}