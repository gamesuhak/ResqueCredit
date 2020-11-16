#include "Title.h"
#include "Input.h"
#include "Bool.h"
#include "Image.h"
#include "Render.h"
#include "Sprite.h"
#include "Screen.h"
#include <stdio.h>

TitleMenuType TitleMenu = TITLEMENU_NONE;
const char* TitleMenuText[TITLEMENU_COUNT] = { "◀ 게임 시작 ▶", "◀ 에디터 ▶", "◀ 종료 ▶" };
const Color TITLEMENU_COLOR = COLOR_BLACK;

extern Bool IsProcess; // GameData.c

extern Bool KeyState[KEY_COUNT]; // InputProcess.c
extern int KeyCharge[KEY_COUNT]; // InputProcess.c

extern Image* Buffer; // Render.c

extern Image** Sprites; // Sprite.c

void TitleProcess()
{
	int time = 100;
	while (True)
	{
		if (time > 10)
		{
			if (PressAnyKey())
			{
				time = 0;
				if (TitleMenu == TITLEMENU_NONE)
				{
					TitleMenu = 0;
					EraseText(TITLEMENU_X, TITLEMENU_Y, SCREEN_WIDTH);
					PrintText(TITLEMENU_X, TITLEMENU_Y, TitleMenuText[TitleMenu], TITLEMENU_COLOR);
					continue;
				}
				if (KeyState[KEY_A])
				{
					IsProcess = False;
					return TitleMenu;
					break;
				}
				if (KeyState[KEY_LEFT])
				{
					--TitleMenu;
					if (TitleMenu < 0)
					{
						TitleMenu = TITLEMENU_COUNT - 1;
					}
				}
				if (KeyState[KEY_RIGHT])
				{
					++TitleMenu;
					TitleMenu %= TITLEMENU_COUNT;
				}
				
				EraseText(TITLEMENU_X, TITLEMENU_Y, SCREEN_WIDTH);
				PrintText(TITLEMENU_X, TITLEMENU_Y, TitleMenuText[TitleMenu], TITLEMENU_COLOR);
			}
		}
		++time;
		Sleep(10);
	}
	return;
}

void InitilizeTitle()
{
	AddImage(0, 0, Sprites[SPRITE_TITLE], Buffer);
	UpdateRender();
	PrintText(TITLEMENU_X, TITLEMENU_Y, "Press Any Key", TITLEMENU_COLOR);
}