#include "Sprite.h"

#include "Image.h"
#include "Object.h" // DIRECTION
#include "FileLoader.h" // LoadBitmapFile

// ���� ������ �� ��������Ʈ ���
Image** Sprites;

// ��������Ʈ�� �̸���
const char* SPRITENAME[SPRITE_COUNT] =
{
	"Map",

	// �÷��̾� ��������Ʈ, 12���� �ִ� ������ ù��° �̹����� �߶� 12���� ����ϱ� ������
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",
	"Finn", "Finn", "Finn",

	"Monster",

	"UI", "UI", "UI",
};

// Sprites�� �ʱ�ȭ�ϴ� �Լ�
void InitializeSprites()
{
	Sprites = (Image**)malloc(sizeof(Image*) * SPRITE_COUNT);
	if (Sprites == NULL) { return; }

	Sprites[SPRITE_MAP] = LoadBitmapFile(SPRITENAME[SPRITE_MAP], COLOR_WHITE);

	Sprites[SPRITE_FINN] = LoadBitmapFile(SPRITENAME[SPRITE_FINN], COLOR_GRAY);
	ParseSprite(SPRITE_FINN, 3, DIRECTION_COUNT);
	SetPivot(SPRITE_FINN, 3 * DIRECTION_COUNT, PIVOT_MIDDLE);

	Sprites[SPRITE_MONSTER] = LoadBitmapFile(SPRITENAME[SPRITE_MONSTER], COLOR_YELLOW);

	Sprites[SPRITE_HEART] = LoadBitmapFile(SPRITENAME[SPRITE_HEART], COLOR_BLACK);
}

// ��������Ʈ�� �����Ͽ� Sprites�� �����ϴ� �޼ҵ� 
// index ������ ��������Ʈ�� ��ȣ, column
void ParseSprite(int index, int column, int row)
{
	Image** images = SliceImage(Sprites[index], column, row);
	for (int i = 0; i < column * row; i++)
	{
		Sprites[index + i] = images[i];
	}
	free(images);
}

// �ϰ������� Sprite�� �߽����� �����ϴ� �޼ҵ�
// index ��������Ʈ�� ù ��ȣ, count = �ϰ������� ������ ����, pivot = ������ Pivot�� ��
void SetPivot(int index, int count, int pivot)
{
	for (int i = 0; i < count; i++)
	{
		if (pivot == PIVOT_LEFTUP)
		{
			Sprites[index + i]->pivot.x = 0;
			Sprites[index + i]->pivot.y = 0;
		}
		else if (pivot == PIVOT_MIDDLE)
		{
			Sprites[index + i]->pivot.x = Sprites[index + i]->width >> 1;
			Sprites[index + i]->pivot.y = Sprites[index + i]->height >> 1;
		}
	}
}