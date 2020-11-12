#pragma once
#include "Image.h"
#include "Map.h"

#define UI_X				0
#define UI_Y				0
#define UI_WIDTH			48
#define UI_HEIGHT			16
#define CAMERA_X			16
#define CAMERA_Y			0
#define CAMERA_WIDTH		48

void Render();
void UpdateRender();
void InitializeRender();

void RenderMap(Room* room, Image* target);
void RenderImage(int x, int y, Image* image);
void UpdateUI(Image* target);
void UpdateAnimation();