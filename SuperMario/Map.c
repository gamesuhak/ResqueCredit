#include "Map.h"
#include <string.h> // memset
#include <stdlib.h> // NULL, malloc

TileData CreateMap(int width, int height)
{
	TileData  tileData = (TileData)malloc(sizeof(char*) * width);
	if (tileData == NULL) { printf("CreateMap1\n"); return NULL; }
	tileData[0] = (char*)malloc(sizeof(char) * width * height);
	if (tileData[0] == NULL) { printf("CreateMap2\n"); return NULL; }
	for (int i = 1; i < width; i++)
	{
		tileData[i] = tileData[i - 1] + height;
		if (tileData[i] == NULL) { printf("CreateMap : %d\n", i); return NULL; }
	}
	memset(tileData[0], 0, sizeof(char) * width * height);
	return tileData;
}