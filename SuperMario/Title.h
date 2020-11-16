#pragma once
#define TITLEMENU_X			0//41
#define TITLEMENU_Y			43
typedef enum TitleMenuType {TITLEMENU_NONE = -1, TITLEMENU_GAME, TITLEMENU_EDIT, TITLEMENU_EXPLAIN, TITLEMENU_EXIT, TITLEMENU_COUNT} TitleMenuType;

void InitilizeTitle();
void TitleProcess();