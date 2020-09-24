#include "Map.h"

typedef enum Tile { TILE_GROUND,  } Tile;
typedef char** TileData;
struct Map
{
	int id; // 고유숫자
	int variety; // 종류
	int width; // 가로길이
	int height; // 세로길이
	TileData tile; // 타일정보
};

void CreateMap(int width, int height)
{

}
