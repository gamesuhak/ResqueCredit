#pragma once
typedef enum Tile { TILE_GROUND = 0, } Tile;

typedef char** TileData;
typedef char** TileTag;

typedef struct Map
{
	int id; // 고유숫자
	int variety; // 종류
	int width; // 가로길이
	int height; // 세로길이
	TileData tile; // 타일정보
	TileTag tag; // 타일태그
} Map;