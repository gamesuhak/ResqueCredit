#pragma once
#include "Image.h"
#include "Stage.h"

#define UI_X				0
#define UI_Y				0
#define UI_WIDTH			88
#define UI_HEIGHT			8
//#define CAMERA_X			16
//#define CAMERA_Y			0
//#define CAMERA_WIDTH		48

void Render();
void UpdateRender();
void InitializeRender();

void StartTransition(Direction direction);
void RenderRoom(Room* room, Image* target);
void RenderImage(int x, int y, Image* image);
void RenderStage(int x, int y, Stage* stage);
void UpdateUI(Image* target);
void UpdateAnimation();
void RenderGame();