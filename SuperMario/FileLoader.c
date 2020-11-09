#include "FileLoader.h"

#include "Bool.h"
#include <stdio.h>
#include <stdlib.h> // malloc ���
#include <string.h> // strcat strok ���

extern int RoomInfoCount;
extern int MonsterInfoCount;

Image* LoadBitmapFile(char* name, Color transparent)
{
	//printf("LoadBitmapFile\n");
	Image* image = (Image*)malloc(sizeof(Image));
	image->id = 0;
	image->pivotx = 0;
	image->pivoty = 0;
	Bitmap tileData;
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
	tileData = NewBitmap(image->width, image->height);
	fseek(file, DATA_START, SEEK_SET);
	// (w & 1)? (w>>1)+1:w>>1;//Ȧ����� ������ ������ ������ ���� +1,¦����� ������
	padding = (4 - (((image->width & 1) ? (image->width >> 1) + 1 : image->width >> 1) % 4)) % 4;

	// ������ ������ ch�� ������ �о����
	for (int y = image->height - 1; y >= 0 ;y--)
	{
		for (char x = 0; x < image->width && (data = fgetc(file)) != EOF; x++)
		{
			tileData[x][y] = data >> 4;

			if (tileData[x][y] == COLOR_DARKBLUE) { tileData[x][y] = COLOR_DARKRED; }
			else if (tileData[x][y] == COLOR_DARKSKY) { tileData[x][y] = COLOR_DARKYELLOW; }
			else if (tileData[x][y] == COLOR_DARKRED) { tileData[x][y] = COLOR_DARKBLUE; }
			else if (tileData[x][y] == COLOR_DARKYELLOW) { tileData[x][y] = COLOR_DARKSKY; }
			else if (tileData[x][y] == COLOR_DARKWHITE) { tileData[x][y] = COLOR_GRAY; }
			else if (tileData[x][y] == COLOR_GRAY) { tileData[x][y] = COLOR_DARKWHITE; }
			else if (tileData[x][y] == COLOR_BLUE) { tileData[x][y] = COLOR_RED; }
			else if (tileData[x][y] == COLOR_SKY) { tileData[x][y] = COLOR_YELLOW; }
			else if (tileData[x][y] == COLOR_RED) { tileData[x][y] = COLOR_BLUE; }
			else if (tileData[x][y] == COLOR_YELLOW) { tileData[x][y] = COLOR_SKY; }
			
			if (x >= image->width)
			{
				break;
			}
			tileData[++x][y] = data % 16;

			if (tileData[x][y] == COLOR_DARKBLUE) { tileData[x][y] = COLOR_DARKRED; }
			else if (tileData[x][y] == COLOR_DARKSKY) { tileData[x][y] = COLOR_DARKYELLOW; }
			else if (tileData[x][y] == COLOR_DARKRED) { tileData[x][y] = COLOR_DARKBLUE; }
			else if (tileData[x][y] == COLOR_DARKYELLOW) { tileData[x][y] = COLOR_DARKSKY; }
			else if (tileData[x][y] == COLOR_DARKWHITE) { tileData[x][y] = COLOR_GRAY; }
			else if (tileData[x][y] == COLOR_GRAY) { tileData[x][y] = COLOR_DARKWHITE; }
			else if (tileData[x][y] == COLOR_BLUE) { tileData[x][y] = COLOR_RED; }
			else if (tileData[x][y] == COLOR_SKY) { tileData[x][y] = COLOR_YELLOW; }
			else if (tileData[x][y] == COLOR_RED) { tileData[x][y] = COLOR_BLUE; }
			else if (tileData[x][y] == COLOR_YELLOW) { tileData[x][y] = COLOR_SKY; }
		}
		fseek(file, padding, SEEK_CUR);
	}
	
	for (char y = 0; y < image->height; y++)
	{
		for (char x = 0; x < image->width; x++)
		{
			(tileData[x][y] == transparent) ? tileData[x][y] = COLOR_TRANSPARENT : 0; // �ش� ������ ���ڷ� ���� ������ ��ġ�ϸ� COLOR_TRANSPARENT�� ����
		}
	}
	image->tileData = tileData;
	return image;
}

RoomInfo* LoadRoomFile(char* name)
{
	RoomInfo* map = (Map*)malloc(sizeof(Map));
	FILE* file = NULL;

	char names[50] = "Map/";
	strcat(names, name);
	strcat(names, ".txt");
	//printf("\"%s\"������ �ε� ��...\n", name);
	if ((file = fopen(names, "rb")) == NULL)
	{

	}
	map->variety = 1;
	map->width = 0;
	map->height = 0;
	map->percentage = 0;
	map->tile = NewTileData(map->width, map->height);
	map->tag = NewTileData(map->width, map->height);
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			map->tile[x][y] = fgetc();
		}
	}
	for (int y = 0; y < map->height; y++)
	{
		for (int x = 0; x < map->width; x++)
		{
			map->tag[x][y] = fgetc();
		}
	}
	//while (fget)
}

MonsterInfo* LoadMonsterFile(char* name)
{
	MonsterInfo* monsterInfo = (MonsterInfo*)malloc(sizeof(MonsterInfo));
	monsterInfo->id;
	monsterInfo->hp;
	monsterInfo->power;
	monsterInfo->speed;
	monsterInfo->object.layer = 1;
	monsterInfo->object.position.x = 1;
	monsterInfo->object.position.y = 1;
	monsterInfo->object.position.y = 1;
	
	return monsterInfo;
}

