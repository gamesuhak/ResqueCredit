#pragma once
typedef enum Tile { TILE_GROUND = 0, } Tile;

typedef char** TileData;
typedef char** TileTag;

typedef struct Map
{
	int id; // ��������
	int variety; // ����
	int width; // ���α���
	int height; // ���α���
	TileData tile; // Ÿ������
	TileTag tag; // Ÿ���±�
} Map;