#include "Map.h"

typedef enum Tile { TILE_GROUND,  } Tile;
typedef char** TileData;
struct Map
{
	int id; // ��������
	int variety; // ����
	int width; // ���α���
	int height; // ���α���
	TileData tile; // Ÿ������
};

void CreateMap(int width, int height)
{

}
