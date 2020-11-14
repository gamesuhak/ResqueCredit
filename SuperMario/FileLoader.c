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

void SaveRoomInfoFile(char* name, RoomInfo* roomInfo)
{
	FILE* file;
	char names[50] = "Map/";
	strcat(names, name);
	strcat(names, ".txt");
	file = fopen(names, "wt");
	if (file == NULL) { return NULL; }
	fprintf(file, "Type : %d\n", roomInfo->type);
	fprintf(file, "Width : %d\n", roomInfo->width);
	fprintf(file, "Height : %d\n", roomInfo->height);
	fprintf(file, "Percentage : %d\n", roomInfo->percentage);
	fprintf(file, "Door : %d\n", roomInfo->door);
	fprintf(file, "MonsterCount : %d\n", roomInfo->monsterCount);

	for (int y = 0; y < roomInfo->height; y++)
	{
		for (int x = 0; x < roomInfo->width; x++)
		{
			fprintf(file, "%d ", roomInfo->tile[x][y]);
		}
		fprintf(file, "\n");
	}
	for (int y = 0; y < roomInfo->height; y++)
	{
		for (int x = 0; x < roomInfo->width; x++)
		{
			fprintf(file, "%d ", roomInfo->tag[x][y]);
		}
		fprintf(file, "\n");
	}
	for (int y = 0; y < roomInfo->height; y++)
	{
		for (int x = 0; x < roomInfo->width; x++)
		{
			fprintf(file, "%d ", roomInfo->monsters[x][y]);
		}
		fprintf(file, "\n");
	}
	return;
}

RoomInfo* LoadRoomInfoFile(char* name)
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
	fscanf(file, "Width : %d\n", &room->width);
	fscanf(file, "Height : %d\n", &room->height);
	fscanf(file, "Percentage : %d\n", &room->percentage);
	fscanf(file, "Door : %d\n", &room->door);
	fscanf(file, "MonsterCount : %d\n", &room->monsterCount);

	room->tile = NewArray(room->width, room->height);
	room->tag = NewArray(room->width, room->height);
	room->monsters = NewArray(room->width, room->height);
	
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			fscanf(file, "%d ", &room->tile[x][y]);
		}
	}
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			fscanf(file, "%d ", &room->tag[x][y]);
		}
	}
	for (int y = 0; y < room->height; y++)
	{
		for (int x = 0; x < room->width; x++)
		{
			fscanf(file, "%d ", &room->monsters[x][y]);
		}
	}
	fclose(file);
	return room;
}

void SaveMonsterInfoFile(char* name, MonsterInfo* monsterInfo)
{
	FILE* file;
	char names[50] = "Monster/";
	strcat(names, name);
	strcat(names, ".txt");
	file = fopen(names, "wt");
	if (file == NULL) { return NULL; }

	fprintf(file, "HP : %d\n", monsterInfo->hp);
	fprintf(file, "Power : %d\n", monsterInfo->power);
	fprintf(file, "Speed : %d\n", monsterInfo->speed);
	fprintf(file, "Layer : %d\n", monsterInfo->object.layer);
	fprintf(file, "Pivot : {%d, %d}\n", monsterInfo->object.collider.pivot.x, monsterInfo->object.collider.pivot.y);
	fprintf(file, "Size : {%d, %d}\n", monsterInfo->object.collider.size.x, monsterInfo->object.collider.size.y);
	return;
}

MonsterInfo* LoadMonsterInfoFile(char* name)
{
	FILE* file;
	char names[50] = "Monster/";
	strcat(names, name);
	strcat(names, ".txt");
	if ((file = fopen(names, "rb")) == NULL) { return NULL; }

	MonsterInfo* monsterInfo = (MonsterInfo*)malloc(sizeof(MonsterInfo));
	if (monsterInfo == NULL) { return NULL; }
	fscanf(file, "HP : %d\n", &monsterInfo->hp);
	fscanf(file, "Power : %d\n", &monsterInfo->power);
	fscanf(file, "Speed : %d\n", &monsterInfo->speed);
	fscanf(file, "Layer : %d\n", &monsterInfo->object.layer);
	fscanf(file, "Pivot : {%d, %d}\n", &monsterInfo->object.collider.pivot.x, &monsterInfo->object.collider.pivot.y);
	fscanf(file, "Size : {%d, %d}\n", &monsterInfo->object.collider.size.x, &monsterInfo->object.collider.size.y);
	fclose(file);
	return monsterInfo;
}